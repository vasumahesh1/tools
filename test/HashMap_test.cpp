#include "HashMap_test.h"
#include "MemoryAllocators/PoolAllocator.h"

TEST_F(HashMapTest, Constructs) {
  auto target = HashMap<U32, const char*>();
}

TEST_F(HashMapTest, BasicInsertTest) {
  auto target = HashMap<U32, const char*>();

  U32 key = mKeyHashOp.evaluate(mKey1, 8);
  const char* value = "MyCustomValue1";
  target.insert(key, value);

  const char* storedValue;

  auto result = target.get(key, &storedValue);

  ASSERT_EQ(strcmp(value, storedValue), 0);
  ASSERT_EQ(result, true);
}

TEST_F(HashMapTest, MultiInsertTest) {
  auto target = HashMap<U32, const char*>();

  U32 key1 = mKeyHashOp.evaluate(mKey1, 8);
  const char* value1 = "MyCustomValue1";

  U32 key2 = mKeyHashOp.evaluate(mKey2, 8);
  const char* value2 = "MyCustomValue2";

  U32 key3 = mKeyHashOp.evaluate(mKey3, 8);
  const char* value3 = "MyCustomValue3";
  target.insert(key1, value1);
  target.insert(key2, value2);
  target.insert(key3, value3);

  const char* storedValue1;
  const char* storedValue2;
  const char* storedValue3;

  auto result3 = target.get(key3, &storedValue3);
  ASSERT_EQ(result3, true);
  ASSERT_EQ(strcmp(value3, storedValue3), 0);

  auto result2 = target.get(key2, &storedValue2);
  ASSERT_EQ(result2, true);
  ASSERT_EQ(strcmp(value2, storedValue2), 0);

  auto result1 = target.get(key1, &storedValue1);
  ASSERT_EQ(result1, true);
  ASSERT_EQ(strcmp(value1, storedValue1), 0);

  ASSERT_NE(strcmp(storedValue1, storedValue2), 0);
  ASSERT_NE(strcmp(storedValue1, storedValue3), 0);
  ASSERT_NE(strcmp(storedValue2, storedValue3), 0);
}

TEST_F(HashMapTest, KeyExistsTest) {
  auto target = HashMap<U32, const char*>();

  U32 key1 = mKeyHashOp.evaluate(mKey1, 8);
  U32 key2 = mKeyHashOp.evaluate(mKey2, 8);
  const char* value1 = "MyCustomValue1";
  target.insert(key1, value1);

  auto result1 = target.exists(key1);
  auto result2 = target.exists(key2);

  ASSERT_EQ(result1, true);
  ASSERT_EQ(result2, false);
}

TEST_F(HashMapTest, WrongKeyGetTest) {
  auto target = HashMap<U32, const char*>();

  U32 key1 = mKeyHashOp.evaluate(mKey1, 8);
  U32 key2 = mKeyHashOp.evaluate(mKey2, 8);
  const char* value1 = "MyCustomValue1";
  target.insert(key1, value1);

  const char* value2 = "JUNK";

  auto result = target.get(key2, &value2);

  ASSERT_EQ(result, false);
  ASSERT_NE(strcmp(value2, value1), 0);
  ASSERT_EQ(strcmp(value2, "JUNK"), 0);
}


TEST_F(HashMapTest, CustomAllocatorTest) {
  PoolAllocator<HashEntry<U32, const char*>> allocatorInstance{ 32 };
  auto target = HashMap<U32, const char*>(&allocatorInstance);

  U32 key1 = mKeyHashOp.evaluate(mKey1, 8);
  const char* value1 = "MyCustomValue1";

  U32 key2 = mKeyHashOp.evaluate(mKey2, 8);
  const char* value2 = "MyCustomValue2";

  U32 key3 = mKeyHashOp.evaluate(mKey3, 8);
  const char* value3 = "MyCustomValue3";
  target.insert(key1, value1);
  target.insert(key2, value2);
  target.insert(key3, value3);

  const char* storedValue1;
  const char* storedValue2;
  const char* storedValue3;

  auto result3 = target.get(key3, &storedValue3);
  ASSERT_EQ(result3, true);
  ASSERT_EQ(strcmp(value3, storedValue3), 0);

  auto result2 = target.get(key2, &storedValue2);
  ASSERT_EQ(result2, true);
  ASSERT_EQ(strcmp(value2, storedValue2), 0);

  auto result1 = target.get(key1, &storedValue1);
  ASSERT_EQ(result1, true);
  ASSERT_EQ(strcmp(value1, storedValue1), 0);

  ASSERT_NE(strcmp(storedValue1, storedValue2), 0);
  ASSERT_NE(strcmp(storedValue1, storedValue3), 0);
  ASSERT_NE(strcmp(storedValue2, storedValue3), 0);
}


TEST_F(HashMapTest, StringKeyTest) {
  auto target = HashMap<const char*, int>();

  const char* key1 = "Test1";
  const char* key2 = "Test2";
  const char* key3 = "Test3";
  const char* key4 = "Test4";

  target.insert(key1, 183);
  target.insert(key2, 1123);
  target.insert(key3, 3423);
  target.insert(key4, 1287);

  int storedValue1;
  int storedValue2;
  int storedValue3;
  int storedValue4;

  auto result1 = target.get(key1, &storedValue1);
  auto result2 = target.get(key2, &storedValue2);
  auto result3 = target.get(key3, &storedValue3);
  auto result4 = target.get(key4, &storedValue4);

  ASSERT_EQ(storedValue1, 183);
  ASSERT_EQ(storedValue2, 1123);
  ASSERT_EQ(storedValue3, 3423);
  ASSERT_EQ(storedValue4, 1287);
  ASSERT_EQ(result1, true);
  ASSERT_EQ(result2, true);
  ASSERT_EQ(result3, true);
  ASSERT_EQ(result4, true);
}
