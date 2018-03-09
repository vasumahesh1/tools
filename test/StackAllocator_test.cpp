#include "StackAllocator_test.h"

TEST(StackAllocatorTest, Constructs) {
  StackAllocator target = StackAllocator(64);
  target.clear();
}

TEST(StackAllocatorTest, NormalAllocation) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(32);
  ASSERT_NE(bytePtr, nullptr);
  target.clear();
}

TEST(StackAllocatorTest, OverflowAllocation1) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(32);
  bytePtr = target.allocate(33);
  ASSERT_EQ(bytePtr, nullptr);
}

TEST(StackAllocatorTest, OverflowAllocation2) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(32);
  bytePtr = target.allocate(32);
  bytePtr = target.allocate(32);
  ASSERT_EQ(bytePtr, nullptr);
}

TEST(StackAllocatorTest, OverflowAllocation3) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(128);
  ASSERT_EQ(bytePtr, nullptr);
}

TEST(StackAllocatorTest, FreeMemory1) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(16);
  UPTR marker = target.getMarker();

  bytePtr = target.allocate(16);
  bytePtr = target.allocate(16);

  target.freeToMarker(marker);

  ASSERT_EQ(marker, target.getMarker());
}

TEST(StackAllocatorTest, ClearTest1) {
  StackAllocator target = StackAllocator(64);
  UPTR marker = target.getMarker();

  void* bytePtr = target.allocate(64);
  target.clear();
  ASSERT_EQ(marker, target.getMarker());
}

