#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

using namespace std;

// How to include this without CMake

// How to link google benchmark
// gcc -I $CONDA_PREFIX/include -L $CONDA_PREFIX/lib -lbenchmark -o cache
// cache.cpp

// gcc -I $CONDA_PREFIX/include -L $CONDA_PREFIX/lib -lbenchmark -o cache
// cache.cpp

// #include "benchmark/benchmark.h"

void row_major(int (&mat)[512][512], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat[i][j] = i + j;
    }
  }
}

void col_major(int (&mat)[512][512], int rows, int cols) {
  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      mat[i][j] = i + j;
    }
  }
}

// Test merge of 2 objects with the same keys, but different values
// static void BM_row_major(benchmark::State &state) {
//     #define ROW 512
//     #define COL 512
//     int mat[ROW][COL];

//     for (auto _ : state)
//     {
//         row_major(mat, ROW, COL);
//     }
// }

// static void BM_col_major(benchmark::State &state) {
//     #define ROW 512
//     #define COL 512
//     int mat[ROW][COL];

//     for (auto _ : state)
//     {
//         col_major(mat, ROW, COL);
//     }
// }

void count_odds(int (&mat)[512][512], int rows, int cols) {
  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (mat[i][j] % 2 == 1) {
        count++;
      }
    }
  }
}

void count_odds_parallel(int (&mat)[512][512], int rows, int cols) {
  // Spawn 6 threads to count the number of odd numbers in the matrix
  // Each thread will count the number of odd numbers in 1/6th of the matrix
  vector<int> odds(6, 0);
  vector<thread> threads;
  for (int i = 0; i < 6; i++) {
    threads.push_back(thread([i, &mat, &odds]() {
      int count = 0;
      // Each thread's row
      for (int j = i * 85; j < (i + 1) * 85; j++) {
        // Columns
        for (int k = 0; k < 512; k++) {
          if (mat[j][k] % 2 == 1) {
            count++;
          }
        }
      }
      odds[i] = count;
    }));
  }

  for (auto &t : threads) {
    t.join();
  }

  int nOdds = std::accumulate(odds.begin(), odds.end(), 0);
}

// static void BM_count_odds(benchmark::State &state) {
//     #define ROW 512
//     #define COL 512
//     #define PROB 0.1

//     int mat[ROW][COL];

//     std::uniform_real_distribution<> dis(0, 1);
//     std::random_device rd;
//     std::mt19937 gen(rd());

//     for (int i = 0; i < ROW; i++)
//     {
//         for (int j = 0; j < COL; j++)
//         {
//             // Generate uniform random double between 0 and 1
//             double p = dis(gen);
//             mat[i][j] = p < PROB ? 1 : 2;
//         }
//     }

//     for (auto _ : state)
//     {
//         count_odds(mat, ROW, COL);
//     }
// }

// BENCHMARK(BM_row_major);
// BENCHMARK(BM_col_major);
// BENCHMARK(BM_count_odds);
// BENCHMARK_MAIN();

int main() {
  // False sharing
  // https://herbsutter.com/2009/05/15/effective-concurrency-eliminate-false-sharing/

#define ROW 512
#define COL 512
#define PROB 0.1

  int mat[ROW][COL];

  std::uniform_real_distribution<> dis(0, 1);
  std::random_device rd;
  std::mt19937 gen(rd());

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      // Generate uniform random double between 0 and 1
      double p = dis(gen);
      mat[i][j] = p < PROB ? 1 : 2;
    }
  }

  // Count milliseconds using chrono
  auto start = std::chrono::high_resolution_clock::now();

  // count_odds(mat, ROW, COL);
  count_odds_parallel(mat, ROW, COL);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;

  // std::cout << "Time taken to count odds (single thread): " <<
  // duration.count() << " ms" << std::endl;
  std::cout << "Time taken to count odds (parallel): " << duration.count()
            << " ms" << std::endl;

  // static int
  // static int

  // global a, b

  // C++ find cache line size
  // https://stackoverflow.com/questions/794632/programmatically-get-the-cache-line-size

  // struct Obj {
  //     alignas(64) int a;
  //     alignas(64) int b;
  // };

  // Memory words

  struct Obj {
    int a;
    int b;
    bool c;
  };

  // #pragma pack

  return 0;
}
