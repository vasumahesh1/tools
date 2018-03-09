#include <iostream>
#include "common.h"
#include "gtest/gtest.h"
#include "StackAllocator_test.h"

TEST(Test, Sanity) {
  EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
  std::cout << "Testing Library Version: " << TOOLS_VERSION_MAJOR << "." << TOOLS_VERSION_MINOR << "." << TOOLS_VERSION_PATCH << std::endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}