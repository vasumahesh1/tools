cmake_minimum_required (VERSION 3.2 FATAL_ERROR)

project (EngineTools)

set (EngineTools_VERSION_MAJOR 0)
set (EngineTools_VERSION_MINOR 1)
set (EngineTools_VERSION_PATCH 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/ToolsCore.h.in"
  "${PROJECT_BINARY_DIR}/ToolsCore.h"
  )

include_directories("${PROJECT_BINARY_DIR}")

add_library(
  EngineTools
  STATIC
  "${PROJECT_SOURCE_DIR}/MemoryAllocators/StackAllocator.cpp"
  "${PROJECT_SOURCE_DIR}/MemoryAllocators/PoolAllocator.h"
  "${PROJECT_SOURCE_DIR}/MemoryAllocators/Allocator.cpp"
  "${PROJECT_SOURCE_DIR}/MemoryAllocators/MonotonicAllocator.h"
  "${PROJECT_SOURCE_DIR}/Utils/Hash.cpp"
  "${PROJECT_SOURCE_DIR}/Containers/HashMap.h"
)
