#include <unordered_map>

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<short, short> numToIndex;
    for (size_t i = 0; i < nums.size(); i++) {
      const int num = nums[i];
      const int other = target - num;
      const short compressedOther = other / 30519;
      if (numToIndex.find(compressedOther) != numToIndex.end()) {
        for (size_t otherIndex = 0; otherIndex < nums.size(); otherIndex++) {
          if (nums[otherIndex] == other && i != otherIndex) {
            return {(int)i, (int)otherIndex};
          }
        }
      }

      const short compressedNum = num / 30519;
      numToIndex[compressedNum] = i;
    }
    return {};  // Should not happen
  }
};
