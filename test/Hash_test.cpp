#include "Hash_test.h"

TEST(HashTest, FNVConstructs) {
  FNVHashOperator target = FNVHashOperator(0x811C9DC5, 0x1000193);
}

TEST(HashTest, FNVNormalAllocation) {
  FNVHashOperator target = FNVHashOperator(0x811C9DC5, 0x1000193);
  const char* str = "engine_test_tools";
  int len = 17;
  auto result = target.evaluate(str, 17);
  ASSERT_EQ(result, 0x1741272c);
}

TEST(HashTest, FNVNormalAllocation2) {
  FNVHashOperator target = FNVHashOperator(0x811C9DC5, 0x1000193);
  const char* str = "32f2389yt23t834kd9saksd93";
  int len = 17;
  auto result = target.evaluate(str, 25);
  ASSERT_EQ(result, 0x1429f4ff);

  str = "engine_test_tools";
  len = 17;
  result = target.evaluate(str, 17);
  ASSERT_EQ(result, 0x1741272c);
}

