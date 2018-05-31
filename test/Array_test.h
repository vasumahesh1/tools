#pragma once
#include "gtest/gtest.h"
#include "MemoryAllocators/MonotonicAllocator.h"
#include "Containers/Array.h"

using namespace EngineTools;

class ArrayTest : public ::testing::Test {
 protected:

  ArrayTest() {
  }

  virtual ~ArrayTest() {
  }

  MonotonicAllocator<16> alloc{4};
};
