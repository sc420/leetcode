class Solution {
 public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.size(); i++) {
      for (size_t j = 0; j < nums.size(); j++) {
        if (i == j) continue;
        if (nums[i] + nums[j] == target) return {(int)i, (int)j};
      }
    }
    return {};  // Should not happen
  }
};
