#include <unordered_map>

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::unordered_map<int, int> numToIndex;
    for (size_t i = 0; i < nums.size(); i++) {
      const int other = target - nums[i];
      if (numToIndex.find(other) == numToIndex.end()) {
        numToIndex[nums[i]] = i;
      } else {
        return {(int)i, numToIndex.at(other)};
      }
    }
    return {};  // Should not happen
  }
};
