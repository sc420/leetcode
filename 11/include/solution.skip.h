#include <algorithm>

class Solution {
 public:
  int maxArea(std::vector<int> &height) {
    int maxArea = 0;
    int prevHeightLeft = 0;
    for (int left = 0; left < height.size(); left++) {
      const int heightLeft = height.at(left);
      if (prevHeightLeft >= heightLeft) continue;

      int prevHeightRight = 0;
      for (int right = height.size() - 1; right > left; right--) {
        const int heightRight = height.at(right);
        if (heightRight <= prevHeightRight) continue;

        const int width = right - left;
        const int minHeight = std::min(heightLeft, heightRight);
        const int area = minHeight * width;
        maxArea = std::max(area, maxArea);
        prevHeightRight = heightRight;
      }
      prevHeightLeft = heightLeft;
    }
    return maxArea;
  }
};
