#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "solution.custom_hash.h"

static const int MAX_NUM = 1000000000;
static const int MAX_SIZE = 1000;
static const int MIN_NUM = -1000000000;
static const unsigned SEED = 1;

struct Problem {
  std::vector<int> nums;
  int target = 0;
  int index1 = -1;
  int index2 = -1;
};

std::mt19937 gen(SEED);

int randInt(const int minValue, const int maxValue) {
  // Reference:
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::uniform_int_distribution<> distrib(minValue, maxValue);
  return distrib(gen);
}

Problem generateProblem(const int size, const int minValue, const int maxValue,
                        const int target) {
  if (target < 2 * minValue || target > 2 * maxValue) {
    throw std::runtime_error("target either too small or too big");
  }

  std::vector<int> nums;
  // Generate numbers in which we can't find the solution
  for (int i = 0; i < size - 2; i++) {
    while (true) {
      const int randNum = randInt(minValue, maxValue);
      for (const auto &num : nums) {
        if (num + randNum == target) {
          continue;
        }
      }
      nums.push_back(randNum);
      break;
    }
  }

  // Generate two numbers as solution
  const int minRandValue = std::max(minValue, target - maxValue);
  const int maxRandValue = std::min(maxValue, target - minValue);
  const int num = randInt(minRandValue, maxRandValue);
  const int other = target - num;
  assert(minValue <= num && num <= maxValue);
  assert(minValue <= other && other <= maxValue);
  nums.push_back(num);
  nums.push_back(other);

  // Randomly shuffle the numbers
  std::shuffle(nums.begin(), nums.end(), gen);

  Problem problem{.nums = nums};
  bool hasRecordedIndex1 = false;
  for (size_t i = 0; i < nums.size(); i++) {
    if (nums[i] == num || nums[i] == other) {
      if (hasRecordedIndex1) {
        problem.index2 = i;
      } else {
        problem.index1 = i;
        hasRecordedIndex1 = true;
      }
    }
  }

  return problem;
}

bool validateOutput(const std::vector<int> &output, const Problem &problem) {
  if (output.size() != 2) return false;
  if (output[0] == problem.index1 && output[1] == problem.index2) return true;
  if (output[0] == problem.index2 && output[1] == problem.index1) return true;
  return false;
}

void printResult(const std::vector<int> &output, const Problem &problem) {
  std::cerr << "----------\n";
  std::cerr << "Input:\n";
  std::cerr << "problem.nums = \n";
  std::cerr << "[ ";
  for (const auto &num : problem.nums) {
    std::cerr << num << " ";
  }
  std::cerr << "]\n";
  std::cerr << "problem.target = " << problem.target << '\n';
  std::cerr << '\n';

  std::cerr << "Output:\n";
  std::cerr << "[ ";
  for (const auto &num : output) {
    std::cerr << num << " ";
  }
  std::cerr << "]\n";

  std::cerr << "Expected:\n";
  std::cerr << "[ " << problem.index1 << " " << problem.index2 << " ]\n";
  std::cerr << "----------\n";
  std::cerr << '\n';
}

int main(int argc, char *argv[]) {
  for (int runIndex = 0; runIndex < 10; runIndex++) {
    const int size = randInt(2, MAX_SIZE);
    const int target = randInt(MIN_NUM, MAX_NUM);
    Problem problem = generateProblem(size, MIN_NUM, MAX_NUM, target);
    problem.target = target;

    Solution solution;
    const std::vector<int> output = solution.twoSum(problem.nums, target);
    if (validateOutput(output, problem)) {
      std::cout << "Accepted\n";
    } else {
      std::cout << "Wrong Answer\n";
      printResult(output, problem);
    }
  }

  return 0;
}
