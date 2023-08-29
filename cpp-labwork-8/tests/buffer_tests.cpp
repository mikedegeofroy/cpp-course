#include <gtest/gtest.h>
#include <lib/CircularBuffer.h>

#include <numeric>
#include <sstream>

// Circular Buffer Tests

class CircularBufferTest : public ::testing::Test {
 protected:
  const size_t kCapacity = 10;
  using Buffer = CircularBuffer<int>;
  Buffer buffer;

  CircularBufferTest() : buffer(kCapacity) {}
};

TEST_F(CircularBufferTest, DefaultConstructor) {
  EXPECT_EQ(buffer.size(), 0);
  EXPECT_EQ(buffer.max_size(), kCapacity);
  EXPECT_TRUE(buffer.empty());
}

TEST_F(CircularBufferTest, ConstructorCountElements) {
  int element = 5;
  size_t count = 3;
  CircularBuffer<int> buffer2(count, element);

  ASSERT_EQ(buffer2.size(), count);
  for (size_t i = 0; i < count; ++i) {
    EXPECT_EQ(buffer2[i], element);
  }
}

TEST_F(CircularBufferTest, CopyConstructor) {
  Buffer buffer2(buffer);

  ASSERT_EQ(buffer.size(), buffer2.size());
  ASSERT_EQ(buffer.front(), buffer2.front());
  ASSERT_EQ(buffer.back(), buffer2.back());
}

TEST_F(CircularBufferTest, FrontBack) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  ASSERT_EQ(buffer.front(), 1);
  ASSERT_EQ(buffer.back(), 3);
}

TEST_F(CircularBufferTest, PushBack) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  ASSERT_EQ(buffer.size(), 3);
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 2);
  EXPECT_EQ(buffer[2], 3);
}

TEST_F(CircularBufferTest, InsertSingleElement) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);
  buffer.insert(buffer.begin() + 1, 4);

  ASSERT_EQ(buffer.size(), 4);
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 4);
  EXPECT_EQ(buffer[2], 2);
  EXPECT_EQ(buffer[3], 3);
}

TEST_F(CircularBufferTest, InsertMultipleElements) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  int element = 4;
  size_t count = 2;
  buffer.insert(buffer.begin() + 1, count, element);

  ASSERT_EQ(buffer.size(), 5);
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 4);
  EXPECT_EQ(buffer[2], 4);
  EXPECT_EQ(buffer[3], 2);
  EXPECT_EQ(buffer[4], 3);
}

TEST_F(CircularBufferTest, Emplace) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);
  buffer.emplace(buffer.begin() + 1, 4);

  ASSERT_EQ(buffer.size(), 4);
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 4);
  EXPECT_EQ(buffer[2], 2);
  EXPECT_EQ(buffer[3], 3);
}

TEST_F(CircularBufferTest, EmplaceBack) {
  buffer.emplace_back(1);
  buffer.emplace_back(2);
  buffer.emplace_back(3);

  ASSERT_EQ(buffer.size(), 3);
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 2);
  EXPECT_EQ(buffer[2], 3);
}


// Separate this into 3 tests
TEST_F(CircularBufferTest, Operators) {
  Buffer buffer2(buffer);

  ASSERT_EQ(buffer == buffer2, true);
  EXPECT_EQ(buffer != buffer2, false);

  Buffer buffer3 = buffer;
  EXPECT_EQ(buffer == buffer3, true);

  buffer.push_back(10);
  buffer.push_back(5);
  buffer.push_back(3);

  EXPECT_EQ(buffer[1], 5);
  EXPECT_EQ(buffer[4], 5);
}

TEST_F(CircularBufferTest, PopFront) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  buffer.pop_front();
  EXPECT_EQ(buffer.size(), 2);
  EXPECT_EQ(buffer.front(), 2);
}

TEST_F(CircularBufferTest, Assign) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);
  std::vector<int> elements_to_assign = {4, 5, 6};
  buffer.assign(elements_to_assign.begin(), elements_to_assign.end());

  ASSERT_EQ(buffer.size(), 3);
  EXPECT_EQ(buffer[0], 4);
  EXPECT_EQ(buffer[1], 5);
  EXPECT_EQ(buffer[2], 6);
}

TEST_F(CircularBufferTest, Swap) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  CircularBuffer<int> buffer2(kCapacity);
  buffer2.push_back(4);
  buffer2.push_back(5);
  buffer2.push_back(6);

  buffer.swap(buffer2);

  ASSERT_EQ(buffer.size(), 3);
  EXPECT_EQ(buffer[0], 4);
  EXPECT_EQ(buffer[1], 5);
  EXPECT_EQ(buffer[2], 6);

  ASSERT_EQ(buffer2.size(), 3);
  EXPECT_EQ(buffer2[0], 1);
  EXPECT_EQ(buffer2[1], 2);
  EXPECT_EQ(buffer2[2], 3);
}

TEST_F(CircularBufferTest, EraseSingleElement) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);
  buffer.erase(buffer.begin() + 1);

  ASSERT_EQ(buffer.size(), 2);
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 3);
}

TEST_F(CircularBufferTest, EraseRange) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);
  buffer.push_back(4);
  buffer.push_back(5);
  buffer.erase(buffer.begin() + 1, buffer.begin() + 4);

  ASSERT_EQ(buffer.size(), 2);
  EXPECT_EQ(buffer[0], 1);
  EXPECT_EQ(buffer[1], 5);
}

TEST_F(CircularBufferTest, Clear) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);
  buffer.clear();

  EXPECT_TRUE(buffer.empty());
  EXPECT_EQ(buffer.size(), 0);
}

TEST_F(CircularBufferTest, Iterators) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  auto it = buffer.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, buffer.end());
}

TEST_F(CircularBufferTest, ConstIterators) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  Buffer::ConstIterator cit = buffer.cbegin();
  EXPECT_EQ(*cit, 1);
  ++cit;
  EXPECT_EQ(*cit, 2);
  ++cit;
  EXPECT_EQ(*cit, 3);
  ++cit;
  EXPECT_EQ(cit, buffer.cend());
}

TEST_F(CircularBufferTest, AlgorithmSupport) {
  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(3);

  int sum = std::accumulate(buffer.begin(), buffer.end(), 0);
  EXPECT_EQ(sum, 6);

  auto found = std::find(buffer.begin(), buffer.end(), 2);
  EXPECT_EQ(*found, 2);
}

// Resizable Circular Buffer Tests

class ExtCircularBufferTest : public ::testing::Test {
 protected:
  const size_t kCapacity = 10;
  using Buffer = ExtCircularBuffer<int>;
  Buffer buffer;

  ExtCircularBufferTest() : buffer(kCapacity) {}
};

TEST_F(ExtCircularBufferTest, Resize) {
  buffer.resize(5);
  EXPECT_EQ(buffer.max_size(), 5);
}
