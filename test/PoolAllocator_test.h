#pragma once
#include "gtest/gtest.h"
#include "MemoryAllocators/PoolAllocator.h"

using namespace EngineTools;

class PoolAllocatorTest : public ::testing::Test {
 protected:

  PoolAllocatorTest() {
  }

  virtual ~PoolAllocatorTest() {
  }
};
