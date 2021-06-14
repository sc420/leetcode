class Solution {
 public:
  int threeSumClosest(std::vector<int> &nums, int target) {
    std::sort(nums.begin(), nums.end());

    const int sz = (int)nums.size();
    for (int i = 0; i < sz - 2; i++) {
      twoSumClosest(nums, target, i + 1);
    }
    return m_closestSum;
  }

  void twoSumClosest(std::vector<int> &nums, const int target, int left) {
    const int num1 = nums[left - 1];
    int right = (int)nums.size() - 1;
    while (left < right) {
      const int sum = num1 + nums[left] + nums[right];
      checkCloser(nums, target, sum);
      if (sum < target) {
        left++;
      } else {
        right--;
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
