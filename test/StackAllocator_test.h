#pragma once
#include "gtest/gtest.h"
#include "MemoryAllocators/StackAllocator.h"

class StackAllocatorTest : public ::testing::Test {
 protected:

  StackAllocatorTest() {
  }

  virtual ~StackAllocatorTest() {
  }
};