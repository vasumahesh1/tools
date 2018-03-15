#include <stdlib.h>
#include "StackAllocator.h"

namespace EngineTools
{
StackAllocator::StackAllocator(U32 stackSizeInBytes)
{
  mCurrentMarker = (Marker) malloc(stackSizeInBytes);
  mBaseMarker = mCurrentMarker;
  mSize = stackSizeInBytes;
}

StackAllocator::~StackAllocator()
{
  free((void*) mBaseMarker);
}

void* StackAllocator::allocate(U32 bytesToAllocate)
{
  Marker addrStart = 0;

  if (bytesToAllocate <= mSize)
  {
    U32 availableBytes = mSize - static_cast<U32>(mCurrentMarker - mBaseMarker);

    if (bytesToAllocate <= availableBytes)
    {

      addrStart = mCurrentMarker;
      mCurrentMarker += bytesToAllocate;
    }
  }

  return reinterpret_cast<void*>(addrStart);
}

void StackAllocator::freeToMarker(Marker marker)
{
  mCurrentMarker = marker;
}

StackAllocator::Marker StackAllocator::getMarker() const
{
  return mCurrentMarker;
}

void StackAllocator::clear()
{
  mCurrentMarker = mBaseMarker;
}

}
