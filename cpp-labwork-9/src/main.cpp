#include <lib/custom_allocator.h>

#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <vector>

int main() {
  size_t kTestIterations = 10000;
  using chrono = std::chrono::high_resolution_clock;

  std::cout << "Vector:\n";

  size_t elem_size = sizeof(int);
  size_t elem_count = 200;
  size_t blockCount = 200;

  MemoryPool memory_pool_1(elem_size * elem_count * 100, blockCount);
  MemoryPool memory_pool_2(elem_size * elem_count * 100 * 4, blockCount);
  MemoryPool memory_pool_3(elem_size * elem_count * 100 * 16, blockCount);

  Allocator<std::string> allocator(
      {&memory_pool_1, &memory_pool_2, &memory_pool_3});

  std::vector<std::string, Allocator<std::string>> vec1(allocator);

  for (auto it : vec1) {
    std::cout << it << "\n";
  }

  // for (int elem_count = 1; elem_count <= 10; ++elem_count) {
  //   float avg1 = 0;
  //   float avg2 = 0;
  //   for (int i = 0; i < kTestIterations; ++i) {
  //     size_t blockCount = 100;

  //     MemoryPool memory_pool_1(elem_size * elem_count * 100, blockCount);
  //     MemoryPool memory_pool_2(elem_size * elem_count * 100 * 4, blockCount);
  //     MemoryPool memory_pool_3(elem_size * elem_count * 100 * 16,
  //     blockCount);

  //     Allocator<std::string> allocator(
  //         {&memory_pool_1, &memory_pool_2, &memory_pool_3});

  //     std::vector<std::string, Allocator<std::string>> vec1(allocator);
  //     std::vector<std::string> vec2;

  //     auto start = chrono::now();
  //     for (int k = 0; k < elem_count * 100; ++k) {
  //       vec1.push_back("hello");
  //     }
  //     auto end = chrono::now();

  //     auto time1 = end - start;

  //     start = chrono::now();
  //     for (int k = 0; k < elem_count * 100; ++k) {
  //       vec2.push_back("hello");
  //     }
  //     end = chrono::now();

  //     auto time2 = end - start;
  //     avg1 += time1.count();
  //     avg2 += time2.count();
  //   }
  //   std::cout << avg1 / kTestIterations << "\t" << avg2 / kTestIterations <<
  //   "\n";
  // }

  // std::cout << "List:\n";

  // elem_size = sizeof(int) + 20;

  // for (int elem_count = 1; elem_count <= 10; ++elem_count) {
  //   float avg1 = 0;
  //   float avg2 = 0;
  //   for (int i = 0; i < kTestIterations; ++i) {
  //     size_t blockCount = elem_count * 100;
  //     MemoryPool memory_pool_1(elem_size, blockCount);

  //     Allocator<int> allocator({&memory_pool_1});

  //     std::list<int, Allocator<int>> list1(allocator);
  //     std::list<int> list2;

  //     auto start = chrono::now();
  //     for (int k = 0; k < elem_count * 100; ++k) {
  //       list1.push_back(k);
  //     }
  //     auto end = chrono::now();

  //     auto time1 = end - start;

  //     start = chrono::now();
  //     for (int k = 0; k < elem_count * 100; ++k) {
  //       list2.push_back(k);
  //     }
  //     end = chrono::now();

  //     auto time2 = end - start;
  //     avg1 += time1.count();
  //     avg2 += time2.count();
  //   }
  //   std::cout << avg1 / kTestIterations << "\t" << avg2 / kTestIterations <<
  //   "\n";
  // }

  // std::cout << "Map:\n";

  // elem_size = sizeof(int) + sizeof(std::string) + 3 * sizeof(void*);

  // for (int elem_count = 1; elem_count <= 10; ++elem_count) {
  //   float avg1 = 0;
  //   float avg2 = 0;
  //   for (int i = 0; i < kTestIterations; ++i) {
  //     size_t blockCount = elem_count * 100;

  //     MemoryPool memory_pool_1(elem_size * elem_count * 100, blockCount);
  //     Allocator<std::pair<const int, std::string>>
  //     allocator({&memory_pool_1});

  //     std::map<int, std::string, std::less<int>,
  //              Allocator<std::pair<const int, std::string>>>
  //         map1(allocator);

  //     std::map<int, std::string> map2;

  //     auto start = chrono::now();
  //     for (int k = 0; k < elem_count * 100; ++k) {
  //       map1[k] = "hello";
  //     }
  //     auto end = chrono::now();

  //     auto time1 = end - start;

  //     start = chrono::now();
  //     for (int k = 0; k < elem_count * 100; ++k) {
  //       map2[k] = "hello";
  //     }
  //     end = chrono::now();

  //     auto time2 = end - start;

  //     // float diff = (float)time2.count() / (float)time1.count();
  //     avg1 += time1.count();
  //     avg2 += time2.count();
  //   }
  //   std::cout << avg1 / kTestIterations << "\t" << avg2 / kTestIterations <<
  //   "\n";
  // }
  return 0;
}
