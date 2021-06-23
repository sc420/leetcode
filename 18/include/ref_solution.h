// Reference: https://leetcode.com/problems/4sum/solution/
class ReferenceSolution {
 public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    std::sort(std::begin(nums), std::end(nums));
    return kSum(nums, target, 0, 4);
  }
  std::vector<std::vector<int>> kSum(std::vector<int> &nums, int target,
                                     int start, int k) {
    std::vector<std::vector<int>> res;
    if (start == nums.size() || nums[start] * k > target ||
        target > nums.back() * k)
      return res;
    if (k == 2) return twoSum(nums, target, start);
    for (int i = start; i < nums.size(); ++i)
      if (i == start || nums[i - 1] != nums[i])
        for (auto &set : kSum(nums, target - nums[i], i + 1, k - 1)) {
          res.push_back({nums[i]});
          res.back().insert(std::end(res.back()), std::begin(set),
                            std::end(set));
        }
    return res;
  }
  std::vector<std::vector<int>> twoSum(std::vector<int> &nums, int target,
                                       int start) {
    std::vector<std::vector<int>> res;
    int lo = start, hi = nums.size() - 1;
    while (lo < hi) {
      int sum = nums[lo] + nums[hi];
      if (sum < target || (lo > start && nums[lo] == nums[lo - 1]))
        ++lo;
      else if (sum > target ||
               (hi < nums.size() - 1 && nums[hi] == nums[hi + 1]))
        --hi;
      else
        res.push_back({nums[lo++], nums[hi--]});
    }
    return res;
  }
};
