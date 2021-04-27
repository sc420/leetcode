class Solution {
 public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    for (size_t i = 0; i < nums.size(); i++) {
      const int num1 = nums[i];
      for (size_t j = 0; j < nums.size(); j++) {
        if (i == j) continue;
        if (num1 + nums[j] == target) return {(int)i, (int)j};
      }
    }
    return {};  // Should not happen
  }
};
