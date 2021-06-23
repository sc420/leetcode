#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <unordered_set>
#include <vector>

#include "ref_solution.h"

// Wrapping include with namespace is bad! Don't do this in practice
namespace leetcode {
namespace sol1 {
#include "solution.leetcode_sol_1.h"
}
namespace optimized {
#include "solution.6.ksum_optimized.h"
}
}  // namespace leetcode

namespace lookup {
namespace naive {
#include "solution.1.lookup.h"
}
namespace two_pointers {
#include "solution.3.lookup_two_pointers.h"
}
}  // namespace lookup

// Problem constraints
static const int MIN_SIZE = 100;
static const int MAX_SIZE = 200;
static const int MIN_NUM = -1000000000;
static const int MAX_NUM = 1000000000;
static const int MIN_TARGET = -1000000000;
static const int MAX_TARGET = 1000000000;
// Problem generation
static const unsigned SEED = 1;
static const int NUM_PROBLEMS_TO_GENERATE = 10;
// Benchmark
static const int BENCHMARK_NUM_REPEAT = 3;

struct Problem {
  std::vector<int> nums;
  int target = 0;
  std::vector<std::vector<int>> expected;
};

static const std::vector<Problem> handmadeProblems = {
    {{1, 0, -1, 0, -2, 2}, 0, {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}}},
    {{}, 0, {}},
    // Added after wrong answer
    {{2, 2, 2, 2, 2}, 8, {{2, 2, 2, 2}}},
    {{-2, -1, -1, 1, 1, 2, 2}, 0, {{-2, -1, 1, 2}, {-1, -1, 1, 1}}},
    {{0, 0, 4, -4, -2, 3}, 8, {}},
    {{-3, -2, -1, 0, 0, 1, 2, 3},
     0,
     {{-3, -2, 2, 3},
      {-3, -1, 1, 3},
      {-3, 0, 0, 3},
      {-3, 0, 1, 2},
      {-2, -1, 0, 3},
      {-2, -1, 1, 2},
      {-2, 0, 0, 2},
      {-1, 0, 0, 1}}},
    {{0, 0, 0, 0}, 0, {{0, 0, 0, 0}}},
    {{-5, 5, 4, -3, 0, 0, 4, -2}, 4, {{-5, 0, 4, 5}, {-3, -2, 4, 5}}},
};

std::mt19937 gen(SEED);

int randInt(const int minValue, const int maxValue) {
  // Reference:
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::uniform_int_distribution<> distrib(minValue, maxValue);
  return distrib(gen);
}

std::vector<std::vector<int>> toSortedList(
    const std::vector<std::vector<int>> &list) {
  std::vector<std::vector<int>> sortedList;
  for (const auto &item : list) {
    std::vector<int> sortedItem(item);
    std::sort(sortedItem.begin(), sortedItem.end());
    sortedList.push_back(sortedItem);
  }
  std::sort(sortedList.begin(), sortedList.end());
  return sortedList;
}

Problem generateRandomProblem(const double scale) {
  Problem problem;
  const int randSize = randInt(scale * MIN_SIZE, scale * MAX_SIZE);
  for (int i = 0; i < randSize; i++) {
    // Divide by 2 to avoid overflow due to summing of 4 numbers
    const int randNum = randInt(MIN_NUM / 2, MAX_NUM / 2);
    problem.nums.push_back(randNum);
  }

  ReferenceSolution solution;
  problem.target = randInt(MIN_TARGET, MAX_TARGET);
  std::vector<int> numsCopied(problem.nums);
  problem.expected = solution.fourSum(numsCopied, problem.target);
  return problem;
}

std::vector<Problem> generateProblems(const double scale) {
  std::vector<Problem> problems = handmadeProblems;
  for (int i = 0; i < NUM_PROBLEMS_TO_GENERATE; i++) {
    problems.push_back(generateRandomProblem(scale));
  }
  return problems;
}

bool validateOutput(const std::vector<std::vector<int>> &output,
                    Problem &problem) {
  const std::vector<std::vector<int>> sortedOutput = toSortedList(output);
  const std::vector<std::vector<int>> sortedExpected =
      toSortedList(problem.expected);
  return sortedOutput == sortedExpected;
}

int benchmarkSolution(
    Problem &problem,
    std::function<std::vector<std::vector<int>>(Problem &)> fn,
    bool &accepted) {
  int totalElapsed = 0;

  for (int i = 0; i < BENCHMARK_NUM_REPEAT; i++) {
    const auto start = std::chrono::high_resolution_clock::now();

    const auto output = fn(problem);

    const auto stop = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    totalElapsed += duration.count();

    accepted = validateOutput(output, problem);
  }

  return totalElapsed / BENCHMARK_NUM_REPEAT;
}

int main(int argc, char *argv[]) {
  std::cout << "Scale,kSum,kSum (Optimized),Lookup,Lookup (Two Pointers)\n";
  for (int scaleFactor = 1; scaleFactor <= 10; scaleFactor++) {
    const double scale = 1 * scaleFactor;
    auto problems = generateProblems(scale);

    std::cerr << "Run benchmark (scale=" << scale << ")\n";

    int totalTimeKSum = 0;
    int totalTimeKSumOptimized = 0;
    int totalTimeLookupNaive = 0;
    int totalTimeLookupTwoPointers = 0;

    for (Problem &problem : problems) {
      bool accepted = false;

      totalTimeKSum += benchmarkSolution(
          problem,
          [](Problem &problem) {
            std::vector<int> numsCopied(problem.nums);
            leetcode::sol1::Solution solution;
            return solution.fourSum(numsCopied, problem.target);
          },
          accepted);
      if (!accepted) {
        std::cerr << "Wrong Answer: leetcode::sol1::Solution\n";
        return 1;
      }

      totalTimeKSumOptimized += benchmarkSolution(
          problem,
          [](Problem &problem) {
            std::vector<int> numsCopied(problem.nums);
            leetcode::optimized::Solution solution;
            return solution.fourSum(numsCopied, problem.target);
          },
          accepted);
      if (!accepted) {
        std::cerr << "Wrong Answer: leetcode::optimized::Solution\n";
        return 1;
      }

      totalTimeLookupNaive += benchmarkSolution(
          problem,
          [](Problem &problem) {
            std::vector<int> numsCopied(problem.nums);
            lookup::naive::Solution solution;
            return solution.fourSum(numsCopied, problem.target);
          },
          accepted);
      if (!accepted) {
        std::cerr << "Wrong Answer: lookup::naive::Solution\n";
        return 1;
      }

      totalTimeLookupTwoPointers += benchmarkSolution(
          problem,
          [](Problem &problem) {
            std::vector<int> numsCopied(problem.nums);
            lookup::two_pointers::Solution solution;
            return solution.fourSum(numsCopied, problem.target);
          },
          accepted);
      if (!accepted) {
        std::cerr << "Wrong Answer: lookup::two_pointers::Solution\n";
        return 1;
      }
    }

    std::cout << scale << "," << totalTimeKSum << "," << totalTimeKSumOptimized
              << "," << totalTimeLookupNaive << ","
              << totalTimeLookupTwoPointers << '\n';
  }

  std::cerr << "Accepted\n";
  return 0;
}
