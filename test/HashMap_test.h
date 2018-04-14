#pragma once
#include "gtest/gtest.h"
#include "Containers/HashMap.h"

using namespace EngineTools;

class HashMapTest : public ::testing::Test {
 protected:

  FNVHashOperator mKeyHashOp;
  const char* mKey1 = "KeyTest1";
  const char* mKey2 = "KeyTest2";
  const char* mKey3 = "KeyTest3";
  const char* mKey4 = "KeyTest4";
  const char* mKey5 = "KeyTest5";
  const char* mKey6 = "KeyTest6";

  HashMapTest(): mKeyHashOp(FNVHashOperator(0x811C9DC5, 0x1000193)) {
  }

  virtual ~HashMapTest() {
  }
};
