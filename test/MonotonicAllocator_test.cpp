#include <limits>
#include <iostream>

#include "MonotonicAllocator_test.h"

struct Sample {
  int arg1;
  double arg2;

  Sample() {
    arg1 = 99;
    arg2 = 16.0;
  }
};

TEST(MonotonicAllocatorTest, Constructs) {
  MonotonicAllocator<> target{ 32 };
}

TEST(MonotonicAllocatorTest, AllocateNormalData) {
  MonotonicAllocator<> target{ 32 };
  Sample* ptr = target.NewObject<Sample>();
  ASSERT_NE(ptr, nullptr);
  ASSERT_EQ(ptr->arg1, 99);
  ASSERT_EQ(ptr->arg2, 16.0);
}

TEST(MonotonicAllocatorTest, AllocateNormalData2) {
  MonotonicAllocator<> target{ 32 };

  uintptr_t base = target.GetBasePtr();

  Sample* ptr = target.NewObject<Sample>();
  Sample* ptr2 = target.NewObject<Sample>();
  ptr2->arg1 = 12;
  ptr2->arg2 = 7.0;

  ASSERT_EQ(base, (uintptr_t) ptr);
  ASSERT_EQ(base + sizeof(Sample), (uintptr_t) ptr2);

  ASSERT_NE(ptr, nullptr);
  ASSERT_EQ(ptr->arg1, 99);
  ASSERT_EQ(ptr->arg2, 16.0);

  ASSERT_NE(ptr2, nullptr);
  ASSERT_EQ(ptr2->arg1, 12);
  ASSERT_EQ(ptr2->arg2, 7.0);
}
