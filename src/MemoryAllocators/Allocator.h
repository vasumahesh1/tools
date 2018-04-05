#pragma once

#include "ToolsCore.h"

namespace EngineTools {
  constexpr SizeType DEFAULT_MEMORY_ALIGNMENT = 16;

  class Allocator {
  public:
    Allocator();
    virtual ~Allocator();

    Allocator(const Allocator& other) = delete;
    Allocator(Allocator&& other) noexcept = delete;
    Allocator& operator=(const Allocator& other) = delete;
    Allocator& operator=(Allocator&& other) noexcept = delete;

    virtual void* Allocate(SizeType size) = 0;
    virtual void Deallocate(void* address) = 0;
    virtual void Reset();

    template <class Type>
    void DeleteObject(const Type* object);

    template <class Type>
    Type* NewObject();
  };

  template <class Type>
  void Allocator::DeleteObject(const Type* object) {
    // TODO: Figure out Dynamic Type based destruction.
    void* address = static_cast<void*>(object);
    object->~Type();
    Deallocate(address);
  }

  template <class Type>
  Type* Allocator::NewObject() {
    Type* address = reinterpret_cast<Type*>(Allocate(sizeof(Type)));
    *address = Type();
    return address;
  }
}
