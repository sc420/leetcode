struct Indexes {
  int lowI1 = 0;
  int lowI2 = 0;
  int highI3 = 0;
  int highI4 = 0;
};

class Solution {
 public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    std::sort(nums.begin(), nums.end());

    const int sz = (int)nums.size();

    std::unordered_map<int, Indexes> sumToIndexes;
    for (int i1 = 0; i1 < sz; i1++) {
      for (int i2 = i1 + 1; i2 < sz; i2++) {
        const int sum = nums[i1] + nums[i2];
        auto itAndInserted = sumToIndexes.insert({sum, {i1, i2, i1, i2}});
        if (!itAndInserted.second) {
          auto it = itAndInserted.first;
          Indexes &indexes = it->second;
          if (i2 - i1 < indexes.lowI2 - indexes.lowI1) {
            indexes.lowI1 = i1;
            indexes.lowI2 = i2;
          }
          if ((i2 - i1 < indexes.highI4 - indexes.highI3) ||
              (i2 - i1 == indexes.highI4 - indexes.highI3 &&
               indexes.highI4 < i2)) {
            indexes.highI3 = i1;
            indexes.highI4 = i2;
          }
        }
      }
    }

    for (int i3 = 0; i3 < sz; i3++) {
      for (int i4 = i3 + 1; i4 < sz; i4++) {
        const int sum3And4 = nums[i3] + nums[i4];
        const int sum1And2 = target - sum3And4;
        const auto it = sumToIndexes.find(sum1And2);
        if (it == sumToIndexes.end()) continue;

        const Indexes &indexesLow = it->second;
        const Indexes &indexesHigh = sumToIndexes[sum3And4];
        if (indexesLow.lowI2 < indexesHigh.highI3) {
          findEqualSums(nums, target, indexesLow.lowI1, indexesLow.lowI2,
                        indexesHigh.highI3, indexesHigh.highI4);
          // Disable the sum since all ohter sums have been found by now
          it->second = {-1, sz, -1, sz};
        }
      }
    }

    return m_output;
  }

  void findEqualSums(const std::vector<int> &nums, const int target,
                     const int lowI1, const int lowI2, const int highI3,
                     const int highI4) {
    const int sz = (int)nums.size();
    const int sum1And2 = nums[lowI1] + nums[lowI2];
    const int sum3And4 = nums[highI3] + nums[highI4];
    int i1 = lowI1, i2 = lowI2, i3 = -1, i4 = sz;
    while (i1 >= 0 && i2 < highI3) {
      const int curSum1And2 = nums[i1] + nums[i2];
      if (curSum1And2 == sum1And2) {
        i3 = highI3;
        i4 = highI4;
        while (i2 < i3 && i4 < sz) {
          const int curSum3And4 = nums[i3] + nums[i4];
          if (curSum3And4 == sum3And4)
            m_output.emplace_back(
                std::vector<int>{nums[i1], nums[i2], nums[i3], nums[i4]});

          if (curSum3And4 >= sum3And4) i3--;
          if (curSum3And4 <= sum3And4) i4++;
          while (i3 >= 0 && nums[i3] == nums[i3 + 1]) i3--;
          while (i4 < sz && nums[i4 - 1] == nums[i4]) i4++;
        }
      }

      if (curSum1And2 >= sum1And2) i1--;
      if (curSum1And2 <= sum1And2) i2++;
      while (i1 >= 0 && nums[i1] == nums[i1 + 1]) i1--;
      while (i2 < highI3 && nums[i2 - 1] == nums[i2]) i2++;
    }
  }

  std::vector<std::vector<int>> m_output;
};
