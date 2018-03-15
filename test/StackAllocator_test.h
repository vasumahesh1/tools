#pragma once
#include "gtest/gtest.h"
#include "MemoryAllocators/StackAllocator.h"

using namespace EngineTools;

class StackAllocatorTest : public ::testing::Test {
 protected:

  StackAllocatorTest() {
  }

  virtual ~StackAllocatorTest() {
  }
};
