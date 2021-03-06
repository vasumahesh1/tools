﻿#pragma once

#include "ToolsCore.h"
#include "Containers/Container.h"
#include "Containers/Vector.h"

namespace EngineTools {
  class Allocator;

  namespace Impl {
    template <SizeType Index, typename... BatchProperties>
    struct Get;

    template <typename First, typename... Rest>
    struct Get<0, First, Rest...> {
      Get() = delete;
      typedef First Type;
    };

    template <SizeType Index, typename First, typename... Rest>
    struct Get<Index, First, Rest...> {
      Get() = delete;
      typedef typename Get<Index - 1, Rest...>::Type Type;
    };
  }

  template <typename... BatchProperties>
  class ArrayBatch {

    template <SizeType Index>
    using Type = typename Impl::Get<Index, BatchProperties...>::Type;

  public:
    ArrayBatch(SizeType elements, Allocator* allocator);

  private:
    Container* mBatchData[sizeof...(BatchProperties)];
    SizeType mElements{0};
  };

  template <typename ... BatchProperties>
  ArrayBatch<BatchProperties...>::ArrayBatch(const SizeType elements, Allocator* allocator)
    : mElements(elements) {}
}
