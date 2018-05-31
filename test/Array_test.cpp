#include "Array_test.h"
#include <algorithm>

TEST_F(ArrayTest, Constructs) {
  Array<int> a{ 16, &alloc };
  ASSERT_EQ(a.GetSize(), 0);
}

TEST_F(ArrayTest, NormalPush) {
  alloc.Reset();
  Array<int> a{ 16, &alloc };

  a.Push(10);
  a.Push(20);
  a.Push(30);

  ASSERT_EQ(a.GetSize(), 3);
  ASSERT_EQ(a[0], 10);
  ASSERT_EQ(a[1], 20);
  ASSERT_EQ(a[2], 30);
}

TEST_F(ArrayTest, NormalPop) {
  alloc.Reset();
  Array<int> a{ 16, &alloc };

  a.Push(10);
  a.Push(20);
  a.Push(30);

  ASSERT_EQ(a.GetSize(), 3);
  ASSERT_EQ(a.Pop(), 30);
  ASSERT_EQ(a.GetSize(), 2);
}

TEST_F(ArrayTest, NormalRemove) {
  alloc.Reset();
  Array<int> a{ 16, &alloc };

  a.Push(10);
  a.Push(20);
  a.Push(30);
  a.Push(40);

  int* backPtr1 = a.GetBackPtr();

  ASSERT_EQ(a.GetSize(), 4);

  a.Remove(20);

  int* backPtr2 = a.GetBackPtr();

  ASSERT_EQ((uintptr_t)backPtr1 - (uintptr_t)backPtr2, sizeof(int));

  ASSERT_EQ(a.GetSize(), 3);
  ASSERT_EQ(a[0], 10);
  ASSERT_EQ(a[1], 30);
  ASSERT_EQ(a[2], 40);

  a.Remove(30);

  ASSERT_EQ(a.GetSize(), 2);
  ASSERT_EQ(a[0], 10);
  ASSERT_EQ(a[1], 40);
}

TEST_F(ArrayTest, NormalFind) {
  alloc.Reset();
  Array<int> a{ 16, &alloc };

  a.Push(10);
  a.Push(20);
  a.Push(30);

  ASSERT_EQ(a.Find(10), 0);
  ASSERT_EQ(a.Find(20), 1);
  ASSERT_EQ(a.Find(30), 2);
  ASSERT_EQ(a.Find(99), -1);
}

TEST_F(ArrayTest, Empty) {
  alloc.Reset();
  Array<int> a{ 16, &alloc };

  ASSERT_EQ(a.IsEmpty(), true);

  a.Push(10);

  ASSERT_EQ(a.IsEmpty(), false);

  a.Push(20);
  a.Push(30);

  ASSERT_EQ(a.IsEmpty(), false);
}

TEST_F(ArrayTest, IteratorLoop) {
  alloc.Reset();
  Array<int> a{ 16, &alloc };


  a.Push(40);
  a.Push(10);
  a.Push(30);
  a.Push(20);

  int c = 0;
  for (auto i = a.Begin(); i != a.End(); ++i) {
    ASSERT_EQ(a[c], *i);
    c++;
  }
}

TEST_F(ArrayTest, IteratorSort) {
  alloc.Reset();
  Array<int> a{ 16, &alloc };

  a.Push(40);
  a.Push(10);
  a.Push(30);
  a.Push(20);

  std::sort(a.Begin(), a.End());

  ASSERT_EQ(a[0], 10);
  ASSERT_EQ(a[1], 20);
  ASSERT_EQ(a[2], 30);
  ASSERT_EQ(a[3], 40);
}
