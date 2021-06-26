struct Item {
  int num = 0;
  int index = 0;
};

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    const int sz = (int)nums.size();

    std::vector<Item> items(sz);
    for (int i = 0; i < sz; i++) {
      items[i].num = nums[i];
      items[i].index = i;
    }

    // Sort the items by numbers
    std::sort(items.begin(), items.end(),
              [](const Item &item1, const Item &item2) {
                return item1.num < item2.num;
              });

    int left = 0, right = sz - 1;
    while (left < right) {
      const int sum = items[left].num + items[right].num;
      if (sum < target) {
        left++;
      } else if (sum > target) {
        right--;
      } else {
        return {items[left].index, items[right].index};
      }
    }
    return {};  // Should not happen
  }
};
