#include <algorithm>

class Solution {
 public:
  int maxArea(std::vector<int> &height) {
    int maxArea = 0;
    for (int left = 0; left < height.size(); left++) {
      const int heightLeft = height.at(left);
      for (int right = height.size() - 1; right > left; right--) {
        const int heightRight = height.at(right);
        const int width = right - left;
        const int minHeight = std::min(heightLeft, heightRight);
        const int area = minHeight * width;
        maxArea = std::max(area, maxArea);
      }
    }
    return maxArea;
  }
};
