#include "Vector_test.h"

TEST_F(VectorTest, Constructs) {
  Vector<int> v{ 16, &alloc };
  ASSERT_EQ(v.GetSize(), 0);
}

TEST_F(VectorTest, NormalPush) {
  alloc.Reset();
  Vector<int> v{ 16, &alloc };

  v.Push(10);
  v.Push(20);
  v.Push(30);

  ASSERT_EQ(v.GetSize(), 3);
  ASSERT_EQ(v[0], 10);
  ASSERT_EQ(v[1], 20);
  ASSERT_EQ(v[2], 30);
}

TEST_F(VectorTest, NormalPop) {
  alloc.Reset();
  Vector<int> v{ 16, &alloc };

  v.Push(10);
  v.Push(20);
  v.Push(30);

  ASSERT_EQ(v.GetSize(), 3);
  ASSERT_EQ(v.Pop(), 30);
  ASSERT_EQ(v.GetSize(), 2);
}

TEST_F(VectorTest, NormalRemove) {
  alloc.Reset();
  Vector<int> v{ 16, &alloc };

  v.Push(10);
  v.Push(20);
  v.Push(30);
  v.Push(40);

  ASSERT_EQ(v.GetSize(), 4);

  v.Remove(20);

  ASSERT_EQ(v.GetSize(), 3);
  ASSERT_EQ(v[0], 10);
  ASSERT_EQ(v[1], 30);
  ASSERT_EQ(v[2], 40);

  v.Remove(30);

  ASSERT_EQ(v.GetSize(), 2);
  ASSERT_EQ(v[0], 10);
  ASSERT_EQ(v[1], 40);
}

TEST_F(VectorTest, NormalFind) {
  alloc.Reset();
  Vector<int> v{ 16, &alloc };

  v.Push(10);
  v.Push(20);
  v.Push(30);

  ASSERT_EQ(v.Find(10), 0);
  ASSERT_EQ(v.Find(20), 1);
  ASSERT_EQ(v.Find(30), 2);
  ASSERT_EQ(v.Find(99), -1);
}
