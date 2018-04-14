#include "HeapMemoryBuffer.h"
#include <cstdlib>

namespace EngineTools {
#if defined(WIN32) || defined(_WIN32)
#include <malloc.h>
#define ALIGNED_ALLOC(alignment, size) \
  _aligned_malloc(size, alignment)

#define ALIGNED_FREE(ptr)  \
  _aligned_free(ptr)

#elif defined(UNIX) || defined(__linux__)
#include <malloc.h>
#define ALIGNED_ALLOC(alignment, size) \
  memalign(alignment, size)

#define ALIGNED_FREE(ptr) \
  free(ptr)

#elif defined(APPLE) || defined(__linux__)
#define ALIGNED_ALLOC(alignment, size) \
  memalign(alignment, size)

#define ALIGNED_FREE(ptr) \
  free(ptr)
#endif

  HeapMemoryBuffer::HeapMemoryBuffer(const SizeType blockSize)
    : MemoryBuffer(blockSize, reinterpret_cast<AddressPtr>(malloc(blockSize))) {}

  HeapMemoryBuffer::HeapMemoryBuffer(SizeType blockSize, SizeType alignment)
    : MemoryBuffer(blockSize, reinterpret_cast<AddressPtr>(ALIGNED_ALLOC(alignment, blockSize))) {}

  HeapMemoryBuffer::~HeapMemoryBuffer() {
    if (mMemoryBlock) {
      free(reinterpret_cast<void*>(mMemoryBlock));
    }
  }

  void* HeapMemoryBuffer::Allocate(SizeType size) {
    const AddressPtr addr = AllocateRaw(size);
    return reinterpret_cast<void*>(addr);
  }

  void HeapMemoryBuffer::Deallocate(void* address) {}

  void* HeapMemoryBuffer::AllocateAligned(SizeType size, SizeType alignment) {
    // Power of 2 check
    assert((alignment & (alignment - 1)) == 0);

    const SizeType totalSize = size + alignment;
    const UPTR rawAddress = AllocateRaw(totalSize);
    const SizeType mask = alignment - 1;
    const UPTR misalignment = (rawAddress & mask);
    const AddressDiff adjustment = alignment - misalignment;

    const UPTR alignedAddress = rawAddress + adjustment;

    assert(adjustment < 256);
    Byte* pAlignedMem = reinterpret_cast<Byte*>(alignedAddress);
    pAlignedMem[-1] = static_cast<Byte>(adjustment);

    return reinterpret_cast<void*>(alignedAddress);
  }

  void HeapMemoryBuffer::DeallocateAligned(void* address, SizeType alignment) {}

  UPTR HeapMemoryBuffer::AllocateRaw(SizeType size) {
    // Available > Size
    assert(mSize - (mCurrentPosition - mMemoryBlock) >= size);

    const AddressPtr addr = mCurrentPosition;
    mCurrentPosition += size;

    return addr;
  }
}
