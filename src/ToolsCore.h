#pragma once

#include <stdint.h>
#include <cstddef>
#include <cassert>

#define TOOLS_VERSION_MAJOR 0
#define TOOLS_VERSION_MINOR 1
#define TOOLS_VERSION_PATCH 0

namespace EngineTools {
  using UINT = unsigned int;
  using U8 = uint8_t;
  using U16 = uint16_t;
  using U32 = uint32_t;
  using U64 = uint64_t;
  using UPTR = uintptr_t;
  using SizeType = std::size_t;
};
