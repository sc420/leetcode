class Solution {
 public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    countNumbers(nums);
    std::sort(nums.begin(), nums.end());
    // Erase the duplicate numbers
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

    const size_t sz = nums.size();
    const auto countEnd = m_count.end();
    std::vector<std::vector<int>> output;

    // num + num + num + num = target
    if (target % 4 == 0) {
      const int num = target / 4;
      const auto it = m_count.find(num);
      if (it != countEnd && it->second >= 4) {
        output.emplace_back(std::vector<int>{num, num, num, num});
      }
    }

    // (other + other + other) + num = target
    // num + (other + other + other) = target
    for (const int num : nums) {
      const int otherSum = target - num;
      const int other = otherSum / 3;
      if (num != other && otherSum % 3 == 0) {
        const auto it = m_count.find(other);
        if (it != countEnd && it->second >= 3) {
          output.emplace_back(std::vector<int>{num, other, other, other});
        }
      }
    }

    // 2 same numbers
    for (const int num : nums) {
      if (m_count[num] < 2) continue;

      // (num + num) + (other + other) = target
      const int otherSum = target - (2 * num);
      const int other = otherSum / 2;
      if (otherSum % 2 == 0 && num < other) {
        const auto it = m_count.find(other);
        if (it != countEnd && it->second >= 2) {
          output.emplace_back(std::vector<int>{num, num, other, other});
        }
      }

      // (num + num) + other1 + other2 = target
      for (size_t i1 = 0; i1 < sz; i1++) {
        const int other1 = nums[i1];
        if (num >= other1) continue;
        const int other2 = target - (2 * num) - other1;
        if (other1 < other2 && m_count.find(other2) != countEnd) {
          output.emplace_back(std::vector<int>{num, num, other1, other2});
        }
      }

      // other1 + (num + num) + other2 = target
      for (size_t i1 = 0; i1 < sz; i1++) {
        const int other1 = nums[i1];
        if (other1 >= num) continue;
        const int other2 = target - (2 * num) - other1;
        if (num < other2 && m_count.find(other2) != countEnd) {
          output.emplace_back(std::vector<int>{other1, num, num, other2});
        }
      }

      // other1 + other2 + (num + num) = target
      for (size_t i2 = 0; i2 < sz; i2++) {
        const int other2 = nums[i2];
        if (other2 >= num) continue;
        const int other1 = target - (2 * num) - other2;
        if (other1 < other2 && m_count.find(other1) != countEnd) {
          output.emplace_back(std::vector<int>{other1, other2, num, num});
        }
      }
    }

    // n1 + n2 + n3 + n4 = target
    const auto res = kSum(nums, target, 0, 4);
    output.insert(output.end(), res.begin(), res.end());
    return output;
  }

  // Copied from LeetCode solution 1 and optimized
  std::vector<std::vector<int>> kSum(std::vector<int> &nums, int target,
                                     int start, int k) {
    if (start == nums.size() || nums[start] * k > target ||
        target > nums.back() * k)
      return {};
    if (k == 2) return twoSum(nums, target, start);

    // Find k-1 largest sum in the tail
    int tailSum = 0;
    for (int i = nums.size() - (k - 1); i < nums.size(); ++i) {
      tailSum += nums[i];
    }

    std::vector<std::vector<int>> res;
    for (int i = start; i < nums.size(); ++i) {
      const int num = nums[i];
      // If so, the largest possible sum in this iteration will not >= target
      if (target > (nums[i] + tailSum)) continue;
      // If so, further sum would only get bigger
      else if (num * k > target)
        return res;

      for (auto &set : kSum(nums, target - num, i + 1, k - 1)) {
        res.push_back({num});
        res.back().insert(std::end(res.back()), std::begin(set), std::end(set));
      }
    }
    return res;
  }

  // Copied from LeetCode solution 1 and optimized
  std::vector<std::vector<int>> &twoSum(std::vector<int> &nums, int target,
                                        int start) {
    static std::vector<std::vector<int>> res;
    res.clear();
    int lo = start, hi = nums.size() - 1;
    int loNum = nums[lo], hiNum = nums[hi];
    int sum = loNum + hiNum;
    while (lo < hi) {
      if (sum < target)
        loNum = nums[++lo];
      else if (sum > target)
        hiNum = nums[--hi];
      else {
        res.emplace_back(std::vector<int>{loNum, hiNum});
        loNum = nums[++lo];
        hiNum = nums[--hi];
      }
      sum = loNum + hiNum;
    }
    return res;
  }

  void countNumbers(const std::vector<int> &nums) {
    for (const int num : nums) {
      auto itemAndInserted = m_count.insert({num, 1});
      if (!itemAndInserted.second) {
        auto itItem = itemAndInserted.first;
        itItem->second++;
      }
    }
  }

  std::unordered_map<int, int> m_count{200};
};
