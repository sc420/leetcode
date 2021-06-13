#include <algorithm>

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::vector<std::vector<int>> output;

    for (const int num : nums) m_count[OFFSET + num]++;
    std::sort(nums.begin(), nums.end());
    // Erase the duplicate numbers
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

    for (size_t index1 = 0; index1 < nums.size(); index1++) {
      const int num1 = nums.at(index1);
      m_count[OFFSET + num1]--;
      for (size_t index2 = index1; index2 < nums.size(); index2++) {
        const int num2 = nums.at(index2);
        if (m_count[OFFSET + num2] <= 0) continue;
        m_count[OFFSET + num2]--;

        const int num3 = -(num1 + num2);
        if (num2 <= num3 && num3 >= MIN_VALUE && num3 <= MAX_VALUE &&
            m_count[OFFSET + num3] > 0) {
          output.push_back({num1, num2, num3});
        }

        m_count[OFFSET + num2]++;
      }
      m_count[OFFSET + num1]++;
    }
    return output;
  }

  static const int MIN_VALUE = -100000;
  static const int MAX_VALUE = 100000;
  static const int OFFSET = (-MIN_VALUE);
  static const int ARRAY_SIZE = MAX_VALUE - MIN_VALUE + 1;

  int m_count[ARRAY_SIZE] = {0};
};
