#include "common.h"

#pragma once

// Stack Allocator based on a header file template provided in
// Game Engine Architecture - Jason Gregory
class StackAllocator {
  public:
    typedef UPTR Marker;

    // Allocates a pool of memory for the stack to use
    explicit StackAllocator(U32 stackSizeInBytes);

    // Deallocates the pool of memory which was being used by the stack
    ~StackAllocator();

    // Allocates a block a memory as long as it can fit in the stack
    // else returns nullptr
    void* allocate(U32 bytesToAllocate);

    // Frees memory till a marker. use getMarker() to get the memory pointer
    // and later free to it when needed
    void freeToMarker(Marker marker);

    // Get the current memory pointer in the stack
    Marker getMarker() const;

    // Empty the stack memory
    void clear();

  private:
    Marker mCurrentMarker;
    Marker mBaseMarker;
    U32 mSize;
};

