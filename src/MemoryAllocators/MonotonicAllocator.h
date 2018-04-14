#pragma once

#include "ToolsCore.h"
#include "Allocator.h"
#include <cstdlib>
#include <malloc.h>

#if defined(WIN32) || defined(_WIN32)
#define ALIGNED_ALLOC(alignment, size) \
  _aligned_malloc(size, alignment)

#define ALIGNED_FREE(ptr) \
  _aligned_free(ptr)

#elif defined(APPLE) || defined(UNIX) || defined(__linux__)
#define ALIGNED_ALLOC(alignment, size) \
  memalign(alignment, size)

#define ALIGNED_FREE(ptr) \
  free(ptr)
#endif


namespace EngineTools {
  template <SizeType AlignmentSize = DEFAULT_MEMORY_ALIGNMENT>
  class MonotonicAllocator : public Allocator {
    using AddressPtr = UPTR;
    using AddressDiff = ptrdiff_t;

  public:
    explicit MonotonicAllocator(SizeType size);
    MonotonicAllocator(SizeType size, void* resource);
    ~MonotonicAllocator() override;

    // Disable Copy & Move
    MonotonicAllocator(const MonotonicAllocator& other) = delete;
    MonotonicAllocator& operator=(const MonotonicAllocator& other) = delete;

    MonotonicAllocator(MonotonicAllocator&& other) noexcept = default;
    MonotonicAllocator& operator=(MonotonicAllocator&& other) noexcept = default;

    /**
     * \brief Allocates a set number of bytes
     * \param size Number of Bytes to Allocate
     * \return Pointer to Memory
     */
    void* Allocate(SizeType size) override;

    /**
     * \brief Currently a No Op.
     * \param address Address to Deallocate
     */
    void Deallocate(void* address) override;

    /**
    * \brief Reset the Memory for fresh new use.
    */
    void Reset() override;

#ifdef TOOLS_TEST
    AddressPtr GetCurrentPtr() const { return mCurrentPosition; };
    AddressPtr GetBasePtr() const { return mMemoryBlock; };
    AddressPtr GetSize() const { return mSize; };
#endif

  private:
    /**
     * \brief Finds the next largest Aligned multiple according to the input size
     * \param size Size of Bytes to Allocate
     * \return Next greatest alignment multiple that can fit `size` bytes
     */
    static SizeType AlignAhead(SizeType size) {
      return (size + (AlignmentSize - 1)) & ~(AlignmentSize - 1);
    }

    SizeType mSize;
    AddressPtr mMemoryBlock;
    AddressPtr mCurrentPosition;
    MemoryBuffer* mBuffer{nullptr};
  };

  template <SizeType AlignmentSize>
  MonotonicAllocator<AlignmentSize>::MonotonicAllocator(SizeType size)
    : mSize(AlignmentSize * size),
      mMemoryBlock(reinterpret_cast<AddressPtr>(ALIGNED_ALLOC(AlignmentSize, mSize))),
      mCurrentPosition(mMemoryBlock) {}

  template <SizeType AlignmentSize>
  MonotonicAllocator<AlignmentSize>::MonotonicAllocator(SizeType size, void* resource)
    : mSize(AlignmentSize * size),
      mMemoryBlock(reinterpret_cast<AddressPtr>(resource)),
      mCurrentPosition(mMemoryBlock) {}

  template <SizeType AlignmentSize>
  MonotonicAllocator<AlignmentSize>::~MonotonicAllocator() {
    ALIGNED_FREE(reinterpret_cast<void*>(mMemoryBlock));
  }

  template <SizeType AlignmentSize>
  void* MonotonicAllocator<AlignmentSize>::Allocate(SizeType size) {
    const SizeType alignedSize = AlignAhead(size);

    assert(mSize - (mCurrentPosition - mMemoryBlock) >= alignedSize);
    const AddressPtr addr = mCurrentPosition;
    mCurrentPosition += alignedSize;
    return reinterpret_cast<void*>(addr);
  }

  template <SizeType AlignmentSize>
  void MonotonicAllocator<AlignmentSize>::Deallocate(void* address) {}

  template <SizeType AlignmentSize>
  void MonotonicAllocator<AlignmentSize>::Reset() {
    mCurrentPosition = mMemoryBlock;
  }
}
