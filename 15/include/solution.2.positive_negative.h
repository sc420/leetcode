#include <map>

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::vector<std::vector<int>> output;
    std::map<int, int> negativeCount;
    std::map<int, int> positiveCount;
    for (const int num : nums) {
      if (num < 0) {
        addMapBy1(negativeCount /*will change*/, num);
      } else {
        addMapBy1(positiveCount /*will change*/, num);
      }
    }

    // 2 negative numbers + 1 positive number
    for (const auto &[num1, count1] : negativeCount) {
      for (auto it = negativeCount.find(num1); it != negativeCount.end();
           it++) {
        const int num2 = it->first;
        if (num1 == num2 && count1 <= 1) continue;

        const int num3 = -(num1 + num2);
        if (num3 < 0) continue;
        if (positiveCount.find(num3) == positiveCount.end()) continue;

        output.push_back({num1, num2, num3});
      }
    }

    // 1 negative number + 2 positive numbers
    for (const auto &[num1, count1] : positiveCount) {
      for (auto it = positiveCount.find(num1); it != positiveCount.end();
           it++) {
        const int num2 = it->first;
        if (num1 == num2 && count1 <= 1) continue;

        const int num3 = -(num1 + num2);
        if (num3 >= 0) continue;
        if (negativeCount.find(num3) == negativeCount.end()) continue;

        output.push_back({num1, num2, num3});
      }
    }

    // Special case: 3 zeros
    if (positiveCount.find(0) != positiveCount.end()) {
      if (positiveCount.at(0) >= 3) {
        output.push_back({0, 0, 0});
      }
    }

    return output;
  }

  void addMapBy1(std::map<int, int> &count, const int num) {
    if (count.find(num) == count.end()) count[num] = 0;
    count[num]++;
  }
};
