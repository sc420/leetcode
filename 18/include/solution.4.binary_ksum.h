class Solution {
 public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    std::sort(nums.begin(), nums.end());
    return binaryKSum(nums, target, 0, 4);
  }

  std::vector<std::vector<int>> binaryKSum(const std::vector<int> &nums,
                                           const int target, const int start,
                                           const int k) {
    if (k == 0) {
      if (target == 0)
        return {{}};
      else
        return {};
    }

    const auto startSums = getStartSums(nums, start, k);
    const auto endSums = getEndSums(nums, start, k);
    const auto itUpper =
        std::upper_bound(startSums.begin(), startSums.end(), target);
    const auto itLower =
        std::lower_bound(endSums.begin(), endSums.end(), target);
    const int searchEnd = start + (itUpper - startSums.begin());
    const int searchStart = start + (itLower - endSums.begin());

    std::vector<std::vector<int>> output;
    for (int i = searchStart; i < searchEnd; i++) {
      const int newTarget = target - nums[i];
      const auto childrenOutput = binaryKSum(nums, newTarget, i + 1, k - 1);
      for (const auto &childItem : childrenOutput) {
        std::vector<int> newItem = {nums[i]};
        newItem.insert(newItem.end(), childItem.begin(), childItem.end());
        output.push_back(newItem);
      }
      while (i + 1 < nums.size() && nums[i] == nums[i + 1]) i++;
    }
    return output;
  }

  std::vector<int> getStartSums(const std::vector<int> &nums, const int start,
                                const int k) {
    const int sz = nums.size();
    const int availableSize = sz - start;
    if (k > availableSize) return {};
    int curSum = 0;
    for (int i = start; i < start + k; i++) curSum += nums[i];
    std::vector<int> values(availableSize - k + 1);
    for (int i = start; i < sz - k + 1; i++) {
      values[i - start] = curSum;
      curSum -= nums[i];
      if (i + k < sz) curSum += nums[i + k];
    }
    return values;
  }

  std::vector<int> getEndSums(const std::vector<int> &nums, const int start,
                              const int k) {
    const int sz = nums.size();
    const int availableSize = sz - start;
    if (k > availableSize) return {};
    int curSum = nums[start];
    for (int i = sz - k + 1; i < sz; i++) curSum += nums[i];
    std::vector<int> values(availableSize - k + 1);
    for (int i = start; i < sz - k + 1; i++) {
      values[i - start] = curSum;
      curSum -= nums[i];
      if (i + 1 < sz) curSum += nums[i + 1];
    }
    return values;
  }
};
