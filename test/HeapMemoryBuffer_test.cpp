#include <limits>
#include <iostream>

#include "HeapMemoryBuffer_test.h"

TEST(HeapMemoryBufferTest, Constructs)
{
  HeapMemoryBuffer target{ 32 };

  ASSERT_NE(target.GetCurrentPtr(), 0);
  ASSERT_NE(target.GetBasePtr(), 0);
  ASSERT_EQ(target.GetSize(), 32);
}

TEST(HeapMemoryBufferTest, AlignedConstruction)
{
  SizeType alignment = 16;

  HeapMemoryBuffer target{ 32, alignment };

  ASSERT_NE(target.GetCurrentPtr(), 0);
  ASSERT_NE(target.GetBasePtr(), 0);
  ASSERT_EQ(target.GetSize(), 32);

  SizeType mask = alignment - 1;

  ASSERT_EQ((target.GetCurrentPtr() & mask), 0);
}

TEST(HeapMemoryBufferTest, AlignedConstruction32)
{
  SizeType alignment = 32;

  HeapMemoryBuffer target{ 128, alignment };

  ASSERT_NE(target.GetCurrentPtr(), 0);
  ASSERT_NE(target.GetBasePtr(), 0);
  ASSERT_EQ(target.GetSize(), 128);

  SizeType mask = alignment - 1;

  ASSERT_EQ((target.GetCurrentPtr() & mask), 0);
}

TEST(HeapMemoryBufferTest, AlignedConstruction256)
{
  SizeType alignment = 256;

  HeapMemoryBuffer target{ 128, alignment };

  ASSERT_NE(target.GetCurrentPtr(), 0);
  ASSERT_NE(target.GetBasePtr(), 0);
  ASSERT_EQ(target.GetSize(), 128);

  SizeType mask = alignment - 1;

  ASSERT_EQ((target.GetCurrentPtr() & mask), 0);
}


TEST(HeapMemoryBufferTest, AllocateNormal)
{
  SizeType alignment = 16;
  SizeType allocateAmount = 32;

  HeapMemoryBuffer target{ 128, alignment };

  auto p1 = target.GetCurrentPtr();

  auto p2 = target.Allocate(allocateAmount);

  auto p3 = target.GetCurrentPtr();

  ASSERT_NE(p2, nullptr);
  ASSERT_EQ(p3 - p1, allocateAmount);
}

TEST(HeapMemoryBufferTest, AllocateAlignedNormal)
{
  SizeType alignment = 16;

  SizeType alignmentOfBlock = 32;
  SizeType allocateAmount = 64;

  HeapMemoryBuffer target{ 128, alignment };

  auto p1 = target.GetCurrentPtr();

  auto p2 = target.AllocateAligned(allocateAmount, alignmentOfBlock);

  auto p3 = target.GetCurrentPtr();

  auto p4 = reinterpret_cast<U8*>(reinterpret_cast<UPTR>(p2) - 1);

  ASSERT_NE(p2, nullptr);

  SizeType mask = alignmentOfBlock - 1;
  ASSERT_EQ((reinterpret_cast<UPTR>(p2) & mask), 0);
}
