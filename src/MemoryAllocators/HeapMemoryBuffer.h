#pragma once

#include "ToolsCore.h"
#include "MemoryBuffer.h"

namespace EngineTools {
  class HeapMemoryBuffer : public MemoryBuffer {
    using AddressPtr = UPTR;
    using AddressDiff = ptrdiff_t;
    using Byte = U8;

  public:
    /**
     * \brief Allocate a Block on the Heap for Usage
     * \param blockSize Size of Memory Block to allocate
     */
    explicit HeapMemoryBuffer(SizeType blockSize);

    /**
     * \brief Allocate a Aligned Block on the Heap for Usage
     * \param blockSize Size of Memory Block to allocate
     * \param alignment Starting Alignment for Block
     */
    HeapMemoryBuffer(SizeType blockSize, SizeType alignment);

    /**
     * \brief Destroys the Heap Allocated Memory
     */
    ~HeapMemoryBuffer();

    // Disabled Copy Ctor
    HeapMemoryBuffer(const HeapMemoryBuffer& other) = delete;
    // Disabled Copy Assignment
    HeapMemoryBuffer& operator=(const HeapMemoryBuffer& other) = delete;

    HeapMemoryBuffer(HeapMemoryBuffer&& other) noexcept = default;
    HeapMemoryBuffer& operator=(HeapMemoryBuffer&& other) noexcept = default;

    void* Allocate(SizeType size) override;
    void Deallocate(void* address) override;

    void* AllocateAligned(SizeType size, SizeType alignment) override;
    void DeallocateAligned(void* address, SizeType alignment) override;

  private:
    UPTR AllocateRaw(SizeType size);
  };
}
