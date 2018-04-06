#pragma once

#include "ToolsCore.h"
#include "MemoryAllocators/Allocator.h"

#include <cstring>

namespace EngineTools {
  template <typename Type>
  class Vector {
  public:
    // TODO: Enable When NewDeleteAllocator is ready
    //explicit Vector(UINT maxSize);
    Vector(UINT maxSize, Allocator* alloc);
    ~Vector();

    // Copy and Move Ctors
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    void Push(const Type& data);
    Type Pop();
    int Find(const Type& data);
    void Remove(const Type& data);

    Type& operator[](UINT idx);
    Type& operator[](UINT idx) const;

    UINT GetSize() const { return mSize; }
    UINT GetMaxSize() const { return mMaxSize; }

  private:
    UINT mSize{0};
    UINT mMaxSize{0};
    Allocator* mAlloc{nullptr};
    Type* mBase{nullptr};
    Type* mBack{nullptr};
  };

  // TODO: Enable When NewDeleteAllocator is ready
  //template <typename Type>
  //Vector<Type>::Vector(const UINT maxSize) : mMaxSize(maxSize), mAlloc(alloc), mBase(mAlloc->NewObjects<Type>(maxSize)) {}

  template <typename Type>
  Vector<Type>::Vector(const UINT maxSize, Allocator* alloc)
    : mMaxSize(maxSize),
      mAlloc(alloc),
      mBase(mAlloc->NewObjects<Type>(maxSize, false)),
      mBack(mBase) {}

  template <typename Type>
  Vector<Type>::~Vector() {
    // TODO: should we check for mAlloc being null? Due to Move?
    mAlloc->DeleteObjects(mBase, mMaxSize);
  }

  template <typename Type>
  Vector<Type>::Vector(const Vector& other)
    : mSize(other.mSize),
      mMaxSize(other.mMaxSize),
      mAlloc(other.mAlloc),
      mBack(other.mBack) {

    // Allocate Memory
    mBase = mAlloc->NewObjects<Type>(mMaxSize, false);

    // Copy over Contents
    std::memcpy(mBase, other.mBase, mMaxSize * sizeof(Type));
  }

  template <typename Type>
  Vector<Type>::Vector(Vector&& other) noexcept
    : mSize(other.mSize),
      mMaxSize(other.mMaxSize),
      mAlloc(other.mAlloc),
      mBase(other.mBase),
      mBack(other.mBack) {
    other.mAlloc = nullptr;
    other.mBase  = nullptr;
    other.mBack  = nullptr;
  }

  template <typename Type>
  Vector<Type>& Vector<Type>::operator=(const Vector& other) {
    if (this == &other)
      return *this;
    mSize    = other.mSize;
    mMaxSize = other.mMaxSize;
    mAlloc   = other.mAlloc;
    mBack    = other.mBack;

    // Allocate Memory
    mBase = mAlloc->NewObjects<Type>(mMaxSize, false);

    // Copy over Contents
    std::memcpy(mBase, other.mBase, mMaxSize * sizeof(Type));

    return *this;
  }

  template <typename Type>
  Vector<Type>& Vector<Type>::operator=(Vector&& other) noexcept {
    if (this == &other)
      return *this;
    mSize    = other.mSize;
    mMaxSize = other.mMaxSize;
    mAlloc   = other.mAlloc;
    mBase    = other.mBase;
    mBack    = other.mBack;

    other.mAlloc = nullptr;
    other.mBase  = nullptr;

    return *this;
  }

  template <typename Type>
  void Vector<Type>::Push(const Type& data) {
    assert(mSize < mMaxSize);

    *mBack = data;
    ++mBack;
    ++mSize;
  }

  template <typename Type>
  Type Vector<Type>::Pop() {
    assert(mSize > 0);

    Type data = *(mBack - 1);
    --mSize;
    --mBack;

    return data;
  }

  template <typename Type>
  int Vector<Type>::Find(const Type& data) {
    Type* start = mBase;

    int idx = -1;

    for (auto itr = 0; itr < mSize; ++itr) {
      if (data == *start) {
        idx = itr;
        break;
      }

      ++start;
    }

    return idx;
  }

  template <typename Type>
  void Vector<Type>::Remove(const Type& data) {
    Type* start   = mBase;
    const int idx = Find(data);

    if (idx >= 0) {
      Type* ptr = start + (idx + 1);

      for (int itr = idx + 1; itr < mSize; ++itr) {
        *(ptr - 1) = *ptr;
        ++ptr;
      }

      --mSize;
    }
  }

  template <typename Type>
  Type& Vector<Type>::operator[](const UINT idx) {
    assert(idx < mSize);
    return *(mBase + idx);
  }

  template <typename Type>
  Type& Vector<Type>::operator[](const UINT idx) const {
    assert(idx < mSize);
    return *(mBase + idx);
  }
}
