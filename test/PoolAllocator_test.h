#pragma once
#include "gtest/gtest.h"
#include "MemoryAllocators/PoolAllocator.h"

class PoolAllocatorTest : public ::testing::Test {
 protected:

  PoolAllocatorTest() {
  }

  virtual ~PoolAllocatorTest() {
  }
};
