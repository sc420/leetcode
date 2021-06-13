class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    countNumbers(nums);

    sortAndMakeUnique(nums /*may change*/);

    findOnePositive(nums);
    findOneNegative(nums);
    findOneZero();
    return m_output;
  }

  void countNumbers(const std::vector<int> &nums) {
    for (const int num : nums) {
      if (num < 0) {
        m_negativeCount[OFFSET + num]++;
      } else {
        m_nonNegativeCount[OFFSET + num]++;
      }
    }
  }

  void sortAndMakeUnique(std::vector<int> &nums) {
    std::sort(nums.begin(), nums.end());
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
  }

  void findOnePositive(const std::vector<int> &nums) {
    // num1(-) + num2(-) + num3(+) = 0
    const int numsSize = nums.size();
    for (size_t index1 = 0; index1 < numsSize; index1++) {
      const int num1 = nums[index1];
      if (num1 >= 0) break;
      for (size_t index2 = index1; index2 < numsSize; index2++) {
        if (index1 == index2 && m_negativeCount[OFFSET + num1] <= 1) continue;
        const int num2 = nums[index2];
        if (num2 >= 0) break;

        const int num3 = -(num1 + num2);
        if (num3 < 0 || num3 > MAX_VALUE) continue;
        if (m_nonNegativeCount[OFFSET + num3] <= 0) continue;

        m_output.push_back({num1, num2, num3});
      }
    }
  }

  void findOneNegative(const std::vector<int> &nums) {
    // num1(+) + num2(+) + num3(-) = 0
    const int numsSize = nums.size();
    for (size_t index1 = 0; index1 < numsSize; index1++) {
      const int num1 = nums[index1];
      if (num1 < 0) continue;
      for (size_t index2 = index1; index2 < numsSize; index2++) {
        if (index1 == index2 && m_nonNegativeCount[OFFSET + num1] <= 1)
          continue;
        const int num2 = nums[index2];

        const int num3 = -(num1 + num2);
        if (num3 < MIN_VALUE || num3 >= 0) continue;
        if (m_negativeCount[OFFSET + num3] <= 0) continue;

        m_output.push_back({num1, num2, num3});
      }
    }
  }

  void findOneZero() {
    if (m_nonNegativeCount[OFFSET + 0] >= 3) {
      m_output.push_back({0, 0, 0});
    }
  }

  static const int MIN_VALUE = -100000;
  static const int MAX_VALUE = 100000;
  static const int OFFSET = (-MIN_VALUE);
  static const int ARRAY_SIZE = MAX_VALUE - MIN_VALUE + 1;

  int m_negativeCount[ARRAY_SIZE] = {0};
  int m_nonNegativeCount[ARRAY_SIZE] = {0};
  std::vector<std::vector<int>> m_output;
};
