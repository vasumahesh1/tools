#pragma once
#include "gtest/gtest.h"
#include "MemoryAllocators/HeapMemoryBuffer.h"

using namespace EngineTools;

class HeapMemoryBufferTest : public ::testing::Test {
 protected:

  HeapMemoryBufferTest() {
  }

  virtual ~HeapMemoryBufferTest() {
  }
};
