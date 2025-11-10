#include <gtest/gtest.h>

#include "vector.h"

TEST(VectorIteratorsTest, BeginTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  alglib::VectorIter<int> iter(v.Begin());
  EXPECT_EQ(*iter, 3);
}

TEST(VectorIteratorsTest, ConstBeginTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  alglib::ConstVectorIter<int> citer(v.ConstBegin());
  EXPECT_EQ(*citer, 3);
}

TEST(VectorIteratorsTest, ReverseBeginTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  alglib::ReverseVectorIter<int> riter(v.ReverseBegin());
  EXPECT_EQ(*riter, 20);
}

TEST(VectorIteratorsTest, ConstReverseBeginTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  alglib::ConstReverseVectorIter<int> criter(v.ConstReverseBegin());
  EXPECT_EQ(*criter, 20);
}

TEST(VectorIteratorsTest, ClassicIterationTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  size_t j = 0;
  for (auto i = v.Begin(); i != v.End(); i++) {
    EXPECT_EQ(*i, v.At(j++));
  }
}

TEST(VectorIteratorsTest, ClassicConstIterationTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  size_t j = 0;
  for (auto i = v.ConstBegin(); i != v.ConstEnd(); i++) {
    EXPECT_EQ(*i, v.At(j++));
  }
}

TEST(VectorIteratorsTest, ClassicReverseIterationTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  size_t j = v.Size() - 1;
  for (auto i = v.ReverseBegin(); i != v.ReverseEnd(); i++) {
    EXPECT_EQ(*i, v.At(j--));
  }
}

TEST(VectorIteratorsTest, ClassicConstReverseIterationTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  size_t j = v.Size() - 1;
  for (auto i = v.ConstReverseBegin(); i != v.ConstReverseEnd(); i++) {
    EXPECT_EQ(*i, v.At(j--));
  }
}

TEST(VectorIteratorsTest, ForEachTest) {
  alglib::Vector<int> v;
  v.Push(3);
  v.Push(6);
  v.Push(12);
  v.Push(1);
  v.Push(20);

  size_t j = 0;
  for (auto i : v) {
    EXPECT_EQ(i, v.At(j++));
  }
}
