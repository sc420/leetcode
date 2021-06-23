#include <algorithm>
#include <array>
#include <cfloat>
#include <climits>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ref_solution.h"
#include "solution.6.ksum_optimized.h"

// Problem constraints
static const int MIN_SIZE = 3;
static const int MAX_SIZE = 200;
static const int MIN_NUM = -1000000000 / 2;
static const int MAX_NUM = 1000000000 / 2;
static const int MIN_TARGET = -1000000000;
static const int MAX_TARGET = 1000000000;
// Problem generation
static const unsigned SEED = 1;
static const int NUM_PROBLEMS_TO_GENERATE = 5;

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

Problem generateRandomProblem() {
  Problem problem;
  const int randSize = randInt(MIN_SIZE, MAX_SIZE);
  for (int i = 0; i < randSize; i++) {
    const int randNum = randInt(MIN_NUM, MAX_NUM);
    problem.nums.push_back(randNum);
  }

  ReferenceSolution solution;
  problem.target = randInt(MIN_TARGET, MAX_TARGET);
  problem.expected = solution.fourSum(problem.nums, problem.target);
  return problem;
}

std::vector<Problem> generateProblems() {
  std::vector<Problem> problems = handmadeProblems;
  for (int i = 0; i < NUM_PROBLEMS_TO_GENERATE; i++) {
    problems.push_back(generateRandomProblem());
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

std::string toString(const std::vector<int> &nums) {
  std::string s = "{";
  for (size_t i = 0; i < nums.size(); i++) {
    if (i > 0) s += ", ";
    s += std::to_string(nums.at(i));
  }
  return s + "}";
}

std::string toString(const std::vector<std::vector<int>> &nums) {
  std::string s = "{";
  for (size_t i = 0; i < nums.size(); i++) {
    if (i > 0) s += ", ";
    s += toString(nums.at(i));
  }
  return s + "}";
}

int main(int argc, char *argv[]) {
  std::vector<Problem> problems = generateProblems();

  for (Problem &problem : problems) {
    Solution solution;
    std::vector<int> copiedNums(problem.nums);
    const auto output = solution.fourSum(copiedNums, problem.target);
    if (!validateOutput(output, problem)) {
      std::cerr << "Wrong Answer\n";
      std::cout << "problem.nums =\n" << toString(problem.nums) << '\n';
      std::cout << "problem.target =\n" << problem.target << '\n';
      std::cout << "problem.expected =\n" << toString(problem.expected) << '\n';
      std::cout << "output =\n" << toString(output) << '\n';
      return 1;
    }
  }

  std::cerr << "Accepted\n";
  return 0;
}
