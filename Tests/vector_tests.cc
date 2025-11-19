#include <gtest/gtest.h>

#include "vector.h"

TEST(VectorTest, DefaultConstructor) {
  alglib::Vector<int> vec;
  EXPECT_EQ(vec.Size(), 0);
  EXPECT_GE(vec.Capacity(), 4);
}

TEST(VectorTest, ElementCountConstructor) {
  alglib::Vector<int> vec(10);
  EXPECT_EQ(vec.Size(), 0);
  EXPECT_EQ(vec.Capacity(), 10);
}

TEST(VectorTest, ValueConstructor) {
  alglib::Vector<int> vec(5, 42);
  EXPECT_EQ(vec.Size(), 0);
  EXPECT_EQ(vec.Capacity(), 5);
}

TEST(VectorTest, BasicPushAndAccess) {
  alglib::Vector<int> vec;
  vec.Push(10);
  vec.Push(20);

  EXPECT_EQ(vec.Size(), 2);
  EXPECT_EQ(vec.At(0), 10);
  EXPECT_EQ(vec.At(1), 20);
}

TEST(VectorTest, CapacityGrowth) {
  alglib::Vector<int> vec;
  const size_t initial_cap = vec.Capacity();

  for (int i{}; i < initial_cap; ++i) vec.Push(i);

  EXPECT_EQ(vec.Capacity(), initial_cap);
  vec.Push(100);
  EXPECT_EQ(vec.Capacity(), initial_cap * 2);
}

TEST(VectorTest, OutOfBoundsAccess) {
  alglib::Vector<int> vec;
  vec.Push(10);

  EXPECT_THROW(vec.At(1), std::runtime_error);
  EXPECT_THROW(vec.At(-1), std::runtime_error);
}

TEST(VectorTest, ConstAccess) {
  alglib::Vector<int> vec;
  vec.Push(42);
  const auto& const_vec = vec;

  EXPECT_EQ(const_vec.At(0), 42);
  EXPECT_THROW(const_vec.At(1), std::runtime_error);
}

TEST(VectorTest, MemoryReallocation) {
  alglib::Vector<int> vec;
  vec.Push(1);
  vec.Push(2);
  const int* old_data = &vec.At(0);

  while (vec.Size() < vec.Capacity()) vec.Push(3);
  vec.Push(4);

  EXPECT_NE(old_data, &vec.At(0));
}

TEST(VectorTest, EmptyVectorOperations) {
  alglib::Vector<int> vec;
  EXPECT_THROW(vec.At(0), std::runtime_error);

  alglib::Vector<int> vec2(10);
  EXPECT_THROW(vec2.At(5), std::runtime_error);
}

TEST(VectorTest, ComplexTypeSupport) {
  alglib::Vector<std::string> str_vec;
  str_vec.Push("test");
  str_vec.Push("string");

  EXPECT_EQ(str_vec.At(0), "test");
  EXPECT_EQ(str_vec.At(1), "string");
}

TEST(VectorTest, ValueInitialization) {
  alglib::Vector<int> vec(3, 100);
  vec.Push(200);
  EXPECT_EQ(vec.At(0), 200);
}

TEST(VectorTest, InitializationSafety) {
  alglib::Vector<int> vec;
  vec.Push(10);
  EXPECT_EQ(vec.At(0), 10);
}

TEST(VectorTest, InsertAtBeginning) {
  alglib::Vector<int> vec;
  vec.Push(2);
  vec.Push(3);

  vec.Insert(1, 0);
  EXPECT_EQ(vec.Size(), 3);
  EXPECT_EQ(vec.At(0), 1);
  EXPECT_EQ(vec.At(1), 2);
  EXPECT_EQ(vec.At(2), 3);
}

TEST(VectorTest, InsertAtEnd) {
  alglib::Vector<int> vec;
  vec.Push(1);
  vec.Push(2);

  vec.Insert(3, 2);
  EXPECT_EQ(vec.Size(), 3);
  EXPECT_EQ(vec.At(2), 3);
}

TEST(VectorTest, InsertInMiddle) {
  alglib::Vector<int> vec;
  vec.Push(1);
  vec.Push(3);

  vec.Insert(2, 1);
  EXPECT_EQ(vec.At(1), 2);
  EXPECT_EQ(vec.At(2), 3);
}

TEST(VectorTest, InsertWithReallocation) {
  alglib::Vector<int> vec;
  vec.Push(1);
  vec.Push(2);
  const size_t initial_cap = vec.Capacity();

  vec.Insert(3, 2);
  EXPECT_EQ(vec.Capacity(), initial_cap);
  EXPECT_EQ(vec.At(2), 3);
}

TEST(VectorTest, InsertInvalidIndex) {
  alglib::Vector<int> vec;
  vec.Push(1);

  EXPECT_THROW(vec.Insert(2, 5), std::runtime_error);
  EXPECT_THROW(vec.Insert(2, -1), std::runtime_error);
}

TEST(VectorTest, InsertIntoEmptyVector) {
  alglib::Vector<int> vec;
  vec.Insert(1, 0);
  EXPECT_EQ(vec.Size(), 1);
  EXPECT_EQ(vec.At(0), 1);
}

TEST(VectorTest, InitializerListConstruct) {
  alglib::Vector<int> v = {2, 5, 12, 3};
  EXPECT_EQ(v.At(1), 5);

  alglib::Vector<int> v2{1, 12, 24, 48};
  EXPECT_EQ(v2.At(2), 24);
}

TEST(VectorTest, INitializerListAssignment) {
  alglib::Vector<int> v;
  v = {1, 4, 12};
  EXPECT_EQ(v.At(1), 4);
}
