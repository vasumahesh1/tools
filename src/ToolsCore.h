#pragma once

#include <stdint.h>
#include <cstddef>
#include <cassert>

#define TOOLS_VERSION_MAJOR @EngineTools_VERSION_MAJOR@
#define TOOLS_VERSION_MINOR @EngineTools_VERSION_MINOR@
#define TOOLS_VERSION_PATCH @EngineTools_VERSION_PATCH@

namespace EngineTools {
  using UINT = unsigned int;
  using U32 = uint32_t;
  using UPTR = uintptr_t;
  using SizeType = std::size_t;
};
