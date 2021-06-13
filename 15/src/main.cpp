#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "solution.4.count.h"
#include "solution.ref.h"

static const int MIN_VALUE = -100000;
static const int MAX_VALUE = 100000;
static const unsigned SEED = 1;

struct Problem {
  std::vector<int> nums;
  std::vector<std::vector<int>> expected;
};

static const std::vector<Problem> handmadeProblems = {
    {{}, {}},
    {{0}, {}},
    {{0, 0, 0}, {{0, 0, 0}}},
    {{-1, 0, 1, 2, -1, -4}, {{-1, -1, 2}, {-1, 0, 1}}},
    {{-5, -4, -3, -2, -1}, {}},
    {{1, 2, 3, 4, 5}, {}},
};

std::mt19937 gen(SEED);

int randInt(const int minValue, const int maxValue) {
  // Reference:
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::uniform_int_distribution<> distrib(minValue, maxValue);
  return distrib(gen);
}

Problem generateProblem(const int size) {
  Problem problem;
  for (int i = 0; i < size; i++) {
    const int randNum = randInt(MIN_VALUE, MAX_VALUE);
    problem.nums.push_back(randNum);
  }

  ReferenceSolution solution;
  problem.expected = solution.threeSum(problem.nums);
  return problem;
}

std::set<std::set<int>> vectorToSet(const std::vector<std::vector<int>> &vec) {
  std::set<std::set<int>> vecAsSet;
  for (const auto &item : vec) {
    std::set<int> itemAsSet(item.begin(), item.end());
    vecAsSet.insert(itemAsSet);
  }
  return vecAsSet;
}

bool validateOutput(const std::vector<std::vector<int>> &output,
                    const Problem &problem) {
  if (output.size() != problem.expected.size()) return false;
  const std::set<std::set<int>> outputAsSet = vectorToSet(output);
  const std::set<std::set<int>> expectedAsSet = vectorToSet(problem.expected);
  return outputAsSet == expectedAsSet;
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
  std::vector<Problem> problems = handmadeProblems;
  for (int i = 0; i < 5; i++) {
    problems.push_back(generateProblem(3000));
  }

  for (Problem &problem : problems) {
    Solution solution;
    const auto output = solution.threeSum(problem.nums);
    if (!validateOutput(output, problem)) {
      std::cout << "Wrong Answer\n";
      std::cout << "problem.nums =\n" << toString(problem.nums) << '\n';
      std::cout << "problem.expected =\n" << toString(problem.expected) << '\n';
      std::cout << "output =\n" << toString(output) << '\n';
      return 1;
    }
  }

  std::cout << "Accepted\n";
  return 0;
}
