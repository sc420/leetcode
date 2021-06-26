class Solution {
 public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    const int sz = (int)nums.size();
    std::vector<int> indexes(sz);
    // Fill indexes with 0, 1, 2, ...
    std::iota(indexes.begin(), indexes.end(), 0);
    // Sort the indexes by numbers
    std::stable_sort(indexes.begin(), indexes.end(),
                     [&nums](const int i1, const int i2) {
                       return nums[i1] < nums[i2];
                     });
    int left = 0, right = sz - 1;
    while (left < right) {
      const int sum = nums[indexes[left]] + nums[indexes[right]];
      if (sum < target) {
        left++;
      } else if (sum > target) {
        right--;
      } else {
        return {indexes[left], indexes[right]};
      }
    }
    return {};  // Should not happen
  }
};
