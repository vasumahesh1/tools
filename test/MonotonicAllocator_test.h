#pragma once
#include "gtest/gtest.h"
#include "MemoryAllocators/MonotonicAllocator.h"

using namespace EngineTools;

class MonotonicAllocatorTest : public ::testing::Test {
 protected:

  MonotonicAllocatorTest() {
  }

  virtual ~MonotonicAllocatorTest() {
  }
};
