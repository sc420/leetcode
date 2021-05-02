#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "solution.moving_lines.h"

constexpr int MAX_ARRAY_SIZE = 1000;
constexpr int MIN_VALUE = -1000000;
constexpr int MAX_VALUE = 1000000;
constexpr int NUM_TEST_CASES = 2000;
constexpr unsigned SEED = 1;

struct Problem {
  std::vector<int> nums1;
  std::vector<int> nums2;

  double median;
};

std::mt19937 gen(SEED);

int randInt(const int minValue, const int maxValue) {
  // Reference:
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::uniform_int_distribution<> distrib(minValue, maxValue);
  return distrib(gen);
}

Problem generateProblem(const int m, const int n, const int minValue,
                        const int maxValue) {
  Problem problem;
  for (int i = 0; i < m; i++) {
    problem.nums1.push_back(randInt(minValue, maxValue));
  }
  for (int i = 0; i < n; i++) {
    problem.nums2.push_back(randInt(minValue, maxValue));
  }
  std::sort(problem.nums1.begin(), problem.nums1.end());
  std::sort(problem.nums2.begin(), problem.nums2.end());

  // Find median
  std::vector<int> merged(problem.nums1);
  merged.insert(merged.end(), problem.nums2.begin(), problem.nums2.end());
  std::sort(merged.begin(), merged.end());
  const int firstNum = merged.at((merged.size() - 1) / 2);
  const int secondNum = merged.at(merged.size() / 2);
  problem.median = (firstNum + secondNum) / 2.0;

  return problem;
}

bool validateOutput(const double output, const Problem &problem) {
  const double diff = fabs(output - problem.median);
  return diff <= std::numeric_limits<double>::epsilon();
}

int main(int argc, char *argv[]) {
  for (int testCaseIndex = 0; testCaseIndex < NUM_TEST_CASES; testCaseIndex++) {
    const int m = randInt(0, MAX_ARRAY_SIZE);
    const int n = randInt(0, MAX_ARRAY_SIZE);
    if (m + n < 1) continue;

    Problem problem = generateProblem(m, n, MIN_VALUE, MAX_VALUE);

    Solution solution;
    const double output =
        solution.findMedianSortedArrays(problem.nums1, problem.nums2);
    if (!validateOutput(output, problem)) {
      std::cout << "Wrong Answer\n";
      return 1;
    }
  }

  std::cout << "Accepted\n";
  return 0;
}
