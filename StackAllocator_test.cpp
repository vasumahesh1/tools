#include <iostream>
#include "UnitTest++/UnitTest++.h"

#include "common.h"
#include "StackAllocator.h"

TEST(Constructs) {
  StackAllocator target = StackAllocator(64);
  target.clear();
}

TEST(NormalAllocation) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(32);
  CHECK(bytePtr != nullptr);
  target.clear();
}

TEST(OverflowAllocation1) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(32);
  bytePtr = target.allocate(33);
  CHECK(bytePtr == nullptr);
}

TEST(OverflowAllocation2) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(32);
  bytePtr = target.allocate(32);
  bytePtr = target.allocate(32);
  CHECK(bytePtr == nullptr);
}

TEST(OverflowAllocation3) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(128);
  CHECK(bytePtr == nullptr);
}

TEST(FreeMemory1) {
  StackAllocator target = StackAllocator(64);
  void* bytePtr = target.allocate(16);
  UPTR marker = target.getMarker();

  bytePtr = target.allocate(16);
  bytePtr = target.allocate(16);

  target.freeToMarker(marker);

  CHECK(marker == target.getMarker());
}

TEST(ClearTest1) {
  StackAllocator target = StackAllocator(64);
  UPTR marker = target.getMarker();

  void* bytePtr = target.allocate(64);
  target.clear();
  CHECK(marker == target.getMarker());
}

int main(int, const char *[]) {
  return UnitTest::RunAllTests();
}

