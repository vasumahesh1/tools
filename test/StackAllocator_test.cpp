#include "StackAllocator_test.h"

TEST(StackAllocatorTest, Constructs) {
  StackAllocator target = StackAllocator(64);
  target.Clear();
}

TEST(StackAllocatorTest, NormalAllocation) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.Allocate(32);
  ASSERT_NE(bytePtr, nullptr);
  target.Clear();
}

TEST(StackAllocatorTest, OverflowAllocation1) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.Allocate(32);
  bytePtr = target.Allocate(33);
  ASSERT_EQ(bytePtr, nullptr);
}

TEST(StackAllocatorTest, OverflowAllocation2) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.Allocate(32);
  bytePtr = target.Allocate(32);
  bytePtr = target.Allocate(32);
  ASSERT_EQ(bytePtr, nullptr);
}

TEST(StackAllocatorTest, OverflowAllocation3) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.Allocate(128);
  ASSERT_EQ(bytePtr, nullptr);
}

TEST(StackAllocatorTest, FreeMemory1) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.Allocate(16);
  UPTR marker = target.GetMarker();

  bytePtr = target.Allocate(16);
  bytePtr = target.Allocate(16);

  target.FreeToMarker(marker);

  ASSERT_EQ(marker, target.GetMarker());
}

TEST(StackAllocatorTest, ClearTest1) {
  StackAllocator target = StackAllocator(64);
  UPTR marker = target.GetMarker();

  void* bytePtr = target.Allocate(64);
  target.Clear();
  ASSERT_EQ(marker, target.GetMarker());
}

