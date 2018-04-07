#pragma once

#include "ToolsCore.h"

namespace EngineTools {
  constexpr SizeType DEFAULT_MEMORY_ALIGNMENT = 16;

  class Allocator {
  public:
    Allocator();
    virtual ~Allocator();

    Allocator(const Allocator& other) = delete;
    Allocator& operator=(const Allocator& other) = delete;

    Allocator(Allocator&& other) noexcept = default;
    Allocator& operator=(Allocator&& other) noexcept = default;

    virtual void* Allocate(SizeType size) = 0;
    virtual void Deallocate(void* address) = 0;
    virtual void Reset();

    template <class Type>
    void DeleteObject(Type* object);

    template <class Type>
    void DeleteObjects(Type* object, UINT count);

    template <class Type>
    Type* NewObject(bool construct = true);

    template <class Type>
    Type* NewObjects(UINT count, bool construct = true);
  };

  template <class Type>
  void Allocator::DeleteObject(Type* object) {
    // TODO: Figure out Dynamic Type based destruction.
    void* address = static_cast<void*>(object);
    object->~Type();
    Deallocate(address);
  }

  template <class Type>
  void Allocator::DeleteObjects(Type* object, const UINT count) {
    void* address = static_cast<void*>(object);
    Type* start = object;

    for (auto itr = 0; itr < count; ++itr) {
      start->~Type();
      ++start;
    }

    // TODO: Figure out Deallocate for Arrays
    Deallocate(address);
  }

  template <class Type>
  Type* Allocator::NewObject(bool construct) {
    Type* address = reinterpret_cast<Type*>(Allocate(sizeof(Type)));

    if (construct) {
      *address = Type();
    }

    return address;
  }

  template <class Type>
  Type* Allocator::NewObjects(const UINT count, bool construct) {
    Type* address = reinterpret_cast<Type*>(Allocate(count * sizeof(Type)));
    Type* start   = address;

    if (construct) {
      for (auto itr = 0; itr < count; ++itr) {
        *start = Type();
        ++start;
      }
    }

    return address;
  }
}
