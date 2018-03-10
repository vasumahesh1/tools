#include <limits>
#include <iostream>

#include "PoolAllocator_test.h"

struct Sample {
  int arg1;
  double arg2;
};

TEST(PoolAllocatorTest, Constructs) {
  PoolAllocator<Sample> target{ 32 };
}

TEST(PoolAllocatorTest, AllocateNormalData) {
  PoolAllocator<Sample> target{ 32 };
  Sample* ptr = target.allocate();
  ASSERT_NE(ptr, nullptr);
}


TEST(PoolAllocatorTest, AllocateNormalDataAlignment) {
  PoolAllocator<Sample> target{ 32 };
  Sample* ptr1 = target.allocate();
  ASSERT_NE(ptr1, nullptr);
  ptr1->arg1 = std::numeric_limits<int>::max();
  ptr1->arg2 = std::numeric_limits<double>::max();

  Sample* ptr2 = target.allocate();
  ASSERT_NE(ptr2, nullptr);
  ptr2->arg1 = std::numeric_limits<int>::min();
  ptr2->arg2 = std::numeric_limits<double>::min();

  Sample* ptr3 = target.allocate();
  ASSERT_NE(ptr3, nullptr);
  ptr3->arg1 = 377;
  ptr3->arg2 = 3.14159;

  ASSERT_EQ(ptr1->arg1, std::numeric_limits<int>::max());
  ASSERT_EQ(ptr1->arg2, std::numeric_limits<double>::max());

  ASSERT_EQ(ptr2->arg1, std::numeric_limits<int>::min());
  ASSERT_EQ(ptr2->arg2, std::numeric_limits<double>::min());

  ASSERT_EQ(ptr3->arg1, 377);
  ASSERT_EQ(ptr3->arg2, 3.14159);

  UPTR iPtr1 = (UPTR) ptr1;
  UPTR iPtr2 = (UPTR) ptr2;
  UPTR iPtr3 = (UPTR) ptr3;

  ASSERT_EQ(iPtr2, iPtr1 + 24);
  ASSERT_EQ(iPtr3, iPtr1 + 48);
  ASSERT_EQ(iPtr3, iPtr2 + 24);
}

TEST(PoolAllocatorTest, AllocateFull) {
  PoolAllocator<Sample> target{ 10 };

  for (int i = 0; i < 10; i++) {
    target.allocate();
  }

  Sample* ptr = target.allocate();

  ASSERT_EQ(ptr, nullptr);
}

TEST(PoolAllocatorTest, DeallocateFull) {
  PoolAllocator<Sample> target{ 10 };

  Sample* results[10];

  for (int i = 0; i < 10; i++) {
    results[i] = target.allocate();
  }

  Sample* ptr = target.allocate();

  ASSERT_EQ(ptr, nullptr);

  for (int i = 0; i < 10; i++) {
    target.deallocate(results[i]);
  }

  for (int i = 0; i < 10; i++) {
    results[i] = target.allocate();
    ASSERT_NE(results[i], nullptr);
  }

  ptr = target.allocate();

  ASSERT_EQ(ptr, nullptr);
}
