#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

// Bad practice here, don't do this in practice
namespace twopointers {
#include "solution.two_pointers.h"
namespace optimized {
#include "solution.two_pointers_optimized.h"
}
}  // namespace twopointers

// Problem constraints
static const int MIN_SIZE = 3;
static const int MAX_SIZE = 1000;
static const int MIN_NUM = -1000;
static const int MAX_NUM = 1000;
static const int MIN_TARGET = -10000;
static const int MAX_TARGET = 10000;
// Problem generation
static const unsigned SEED = 1;
static const int NUM_PROBLEMS_TO_GENERATE = 5;
// Benchmark
static const int BENCHMARK_NUM_REPEAT = 3;

struct Problem {
  std::vector<int> nums;
  int target = 0;
  int expected = 0;
};

static const std::vector<Problem> handmadeProblems = {
    {{-1, 2, 1, -4}, 1, 2},
    {{0, 0, 0}, 100, 0},
    {{0, 0, 0}, -100, 0},
};

std::mt19937 gen(SEED);

int randInt(const int minValue, const int maxValue) {
  // Reference:
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::uniform_int_distribution<> distrib(minValue, maxValue);
  return distrib(gen);
}

Problem generateProblem(const int scale) {
  Problem problem;
  const int randSize = randInt(scale * MIN_SIZE, scale * MAX_SIZE);
  for (int i = 0; i < randSize; i++) {
    const int randNum = randInt(scale * MIN_NUM, scale * MAX_NUM);
    problem.nums.push_back(randNum);
  }

  twopointers::optimized::Solution solution;
  problem.target = randInt(scale * MIN_TARGET, scale * MAX_TARGET);
  problem.expected = solution.threeSumClosest(problem.nums, problem.target);
  return problem;
}

std::vector<Problem> generateProblems(const int scale) {
  std::vector<Problem> problems = handmadeProblems;
  for (int i = 0; i < NUM_PROBLEMS_TO_GENERATE; i++) {
    problems.push_back(generateProblem(scale));
  }
  return problems;
}

bool validateOutput(const int output, Problem &problem) {
  return output == problem.expected;
}

int benchmarkSolution(Problem &problem, std::function<int(Problem &)> fn,
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
  std::cout << "Scale,Two pointers,Two pointers (optimized)\n";
  for (int scaleExp = 0; scaleExp < 7; scaleExp++) {
    const int scale = std::pow(2, scaleExp);
    auto problems = generateProblems(scale);

    int totalTimeTwoPointers = 0;
    int totalTimeTwoPointersOptimized = 0;

    for (Problem &problem : problems) {
      bool accepted = false;

      totalTimeTwoPointers += benchmarkSolution(
          problem,
          [](Problem &problem) {
            twopointers::Solution solution;
            return solution.threeSumClosest(problem.nums, problem.target);
          },
          accepted);
      if (!accepted) {
        std::cerr << "Wrong Answer\n";
        return 1;
      }

      totalTimeTwoPointersOptimized += benchmarkSolution(
          problem,
          [](Problem &problem) {
            twopointers::optimized::Solution solution;
            return solution.threeSumClosest(problem.nums, problem.target);
          },
          accepted);
      if (!accepted) {
        std::cerr << "Wrong Answer\n";
        return 1;
      }
    }

    std::cout << scale << "," << totalTimeTwoPointers << ","
              << totalTimeTwoPointersOptimized << '\n';
  }

  std::cerr << "Accepted\n";
  return 0;
}
