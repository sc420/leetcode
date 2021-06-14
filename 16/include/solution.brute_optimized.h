class Solution {
 public:
  int threeSumClosest(std::vector<int> &nums, int target) {
    std::sort(nums.begin(), nums.end());

    const int sz = (int)nums.size();
    for (int i = 0; i < sz - 2; i++) {
      const int lowestSum = nums[i] + nums[i + 1] + nums[i + 2];
      const int highestSum = nums[i] + nums[sz - 2] + nums[sz - 1];
      if (lowestSum <= target && target <= highestSum) {
        twoSumClosest(nums, target, i);
      } else {
        checkCloser(nums, target, lowestSum);
        checkCloser(nums, target, highestSum);
      }
    }
    return m_closestSum;
  }

  void twoSumClosest(std::vector<int> &nums, const int target, int i) {
    const int sz = (int)nums.size();
    const int num1 = nums[i];
    for (int j = i + 1; j < sz; j++) {
      const int num2 = nums[j];
      for (int k = j + 1; k < sz; k++) {
        const int sum = num1 + num2 + nums[k];
        checkCloser(nums, target, sum);
      }
    }
  }

  void checkCloser(const std::vector<int> &nums, const int target,
                   const int sum) {
    const int diff = std::abs(sum - target);
    if (diff < m_minDiff) {
      m_closestSum = sum;
      m_minDiff = diff;
    }
  }

  int m_closestSum = 0;
  int m_minDiff = 99999;
};
