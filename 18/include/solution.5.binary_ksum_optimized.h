class Solution {
 public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    std::sort(nums.begin(), nums.end());
    return binaryKSum(nums, target, 0, 4);
  }

  std::vector<std::vector<int>> binaryKSum(const std::vector<int> &nums,
                                           const int target, const int start,
                                           const int k) {
    // if (k == 0) {
    //   if (target == 0)
    //     return {{}};
    //   else
    //     return {};
    // }
    if (k == 2) return twoSum(nums, target, start);

    const int sz = (int)nums.size();
    const int searchStart =
        findSearchStartByLowerBound(nums, start, sz - k + 1, target, k);
    const int searchEnd =
        findSearchEndByUpperBound(nums, start, sz - k + 1, target, k);

    std::vector<std::vector<int>> output;
    std::vector<int> newItem(k);
    for (int i = searchStart; i < searchEnd; i++) {
      const int newTarget = target - nums[i];
      const auto childrenOutput = binaryKSum(nums, newTarget, i + 1, k - 1);
      for (const auto &childItem : childrenOutput) {
        newItem[0] = nums[i];
        for (size_t j = 0; j < childItem.size(); j++)
          newItem[1 + j] = childItem[j];
        output.push_back(newItem);
      }
      while (i + 1 < sz && nums[i] == nums[i + 1]) i++;
    }
    return output;
  }

  int findSearchStartByLowerBound(const std::vector<int> &nums, int first,
                                  const int last, const int target,
                                  const int k) {
    const auto numsEnd = nums.end();
    int curIndex = 0;
    int count = last - first;
    while (count > 0) {
      const int step = count / 2;
      curIndex = first + step;
      int curSum = nums[curIndex];
      curSum += std::accumulate(numsEnd - k + 1, numsEnd, 0);
      if (curSum < target) {
        first = ++curIndex;
        count -= step + 1;
      } else
        count = step;
    }
    return first;
  }

  int findSearchEndByUpperBound(const std::vector<int> &nums, int first,
                                const int last, const int target, const int k) {
    const auto numsBegin = nums.begin();
    int curIndex = 0;
    int count = last - first;
    while (count > 0) {
      const int step = count / 2;
      curIndex = first + step;
      const int curSum =
          std::accumulate(numsBegin + curIndex, numsBegin + curIndex + k, 0);
      if (!(target < curSum)) {
        first = ++curIndex;
        count -= step + 1;
      } else
        count = step;
    }
    return first;
  }

  std::vector<std::vector<int>> twoSum(const std::vector<int> &nums,
                                       const int target, const int start) {
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
