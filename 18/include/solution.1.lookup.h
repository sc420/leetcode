class Solution {
  using Arr2d = std::array<size_t, 2>;

 public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    std::set<std::vector<int>> items;

    std::sort(nums.begin(), nums.end());

    std::unordered_map<int, std::vector<Arr2d>> sumToIndexesList;
    for (size_t i = 0; i < nums.size(); i++) {
      for (size_t j = i + 1; j < nums.size(); j++) {
        const int sumAB = nums[i] + nums[j];
        sumToIndexesList[sumAB].push_back({i, j});
      }
    }

    for (size_t i = 0; i < nums.size(); i++) {
      for (size_t j = i + 1; j < nums.size(); j++) {
        const int sumCD = nums[i] + nums[j];
        const int sumAB = target - sumCD;
        const auto it = sumToIndexesList.find(sumAB);
        if (it == sumToIndexesList.end()) continue;
        for (const auto &indexes : it->second) {
          if (indexes[1] >= i) continue;
          const int num1 = nums[indexes[0]];
          const int num2 = nums[indexes[1]];
          const int num3 = nums[i];
          const int num4 = nums[j];
          items.insert({num1, num2, num3, num4});
        }
      }
    }

    const std::vector<std::vector<int>> output(items.begin(), items.end());
    return output;
  }
};
