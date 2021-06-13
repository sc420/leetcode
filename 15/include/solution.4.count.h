class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::vector<std::vector<int>> output;

    for (const int num : nums) {
      if (num < 0) {
        m_negativeCount[OFFSET + num]++;
      } else {
        m_positiveCount[OFFSET + num]++;
      }
    }

    std::sort(nums.begin(), nums.end());
    // Erase the duplicate numbers
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    const int numsSize = nums.size();

    // 2 negative numbers + 1 positive number
    size_t index1 = 0;
    for (; index1 < numsSize; index1++) {
      const int num1 = nums[index1];
      if (num1 >= 0) break;
      for (size_t index2 = index1; index2 < numsSize; index2++) {
        if (index1 == index2 && m_negativeCount[OFFSET + num1] <= 1) continue;
        const int num2 = nums[index2];
        if (num2 >= 0) break;

        const int num3 = -(num1 + num2);
        if (num3 < 0 || num3 > MAX_VALUE) continue;
        if (m_positiveCount[OFFSET + num3] <= 0) continue;

        output.push_back({num1, num2, num3});
      }
    }

    // 1 negative number + 2 positive numbers
    for (; index1 < numsSize; index1++) {
      const int num1 = nums[index1];
      if (num1 < 0) continue;
      for (size_t index2 = index1; index2 < numsSize; index2++) {
        if (index1 == index2 && m_positiveCount[OFFSET + num1] <= 1) continue;
        const int num2 = nums[index2];

        const int num3 = -(num1 + num2);
        if (num3 < MIN_VALUE || num3 >= 0) continue;
        if (m_negativeCount[OFFSET + num3] <= 0) continue;

        output.push_back({num1, num2, num3});
      }
    }

    // Special case: 3 zeros
    if (m_positiveCount[OFFSET + 0] >= 3) {
      output.push_back({0, 0, 0});
    }

    return output;
  }

  static const int MIN_VALUE = -100000;
  static const int MAX_VALUE = 100000;
  static const int OFFSET = (-MIN_VALUE);
  static const int ARRAY_SIZE = MAX_VALUE - MIN_VALUE + 1;

  int m_positiveCount[ARRAY_SIZE] = {0};
  int m_negativeCount[ARRAY_SIZE] = {0};
};
