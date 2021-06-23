class Solution {
  using Arr2d = std::array<size_t, 2>;

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
    const int targetOneQuarter = target / 4;
    const int targetOneHalf = target / 2;
    for (size_t i1 = 0; i1 < sz; i1++) {
      const int num1 = nums[i1];
      if (num1 >= targetOneQuarter) continue;

      for (size_t i2 = i1 + 1; i2 < sz; i2++) {
        const int num2 = nums[i2];
        const int sum1And2 = num1 + num2;
        if (sum1And2 >= targetOneHalf) continue;

        // Two pointers
        size_t i3 = i2 + 1;
        size_t i4 = sz - 1;
        while (i3 < i4) {
          const int num3 = nums[i3];
          const int num4 = nums[i4];
          const int sum = sum1And2 + num3 + num4;
          if (sum < target) {
            i3++;
          } else if (sum > target) {
            i4--;
          } else {
            output.emplace_back(std::vector<int>{num1, num2, num3, num4});
            i3++;
            i4--;
          }
        }
      }
    }

    return output;
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
