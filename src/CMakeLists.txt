cmake_minimum_required (VERSION 3.2)

project (EngineTools)

set (EngineTools_VERSION_MAJOR 0)
set (EngineTools_VERSION_MINOR 1)
set (EngineTools_VERSION_PATCH 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/common.h.in"
  "${PROJECT_BINARY_DIR}/common.h"
  )

include_directories("${PROJECT_BINARY_DIR}")

add_library(
  EngineTools
  STATIC
  MemoryAllocators/StackAllocator.cpp
)