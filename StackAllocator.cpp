#include <stdlib.h>
#include "StackAllocator.h"

StackAllocator::StackAllocator(U32 stackSizeInBytes) {
  mCurrentMarker = (Marker) malloc(stackSizeInBytes);
  mBaseMarker = mCurrentMarker;
  mSize = stackSizeInBytes;
}

StackAllocator::~StackAllocator() {
  free((void*) mBaseMarker);
}

void* StackAllocator::allocate(U32 bytesToAllocate) {
  if (bytesToAllocate > mSize) {
    return nullptr;
  }

  U32 availableBytes = mSize - static_cast<U32>(mCurrentMarker - mBaseMarker);

  if (bytesToAllocate > availableBytes) {
    return nullptr;
  }

  Marker addrStart = mCurrentMarker;
  mCurrentMarker += bytesToAllocate;

  return reinterpret_cast<void*>(addrStart);
}

void StackAllocator::freeToMarker(Marker marker) {
  mCurrentMarker = marker;
}

StackAllocator::Marker StackAllocator::getMarker() const {
  return mCurrentMarker;
}

void StackAllocator::clear() {
  mCurrentMarker = mBaseMarker;
}


