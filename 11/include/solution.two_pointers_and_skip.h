#include <algorithm>

class Solution {
 public:
  int maxArea(std::vector<int> &height) {
    int maxArea = 0;
    int left = 0;
    int right = height.size() - 1;
    int prevHeightLeft = 0, prevHeightRight = 0;
    while (left < right) {
      const int width = right - left;
      const int heightLeft = height.at(left);
      const int heightRight = height.at(right);
      if (prevHeightLeft >= heightLeft) {
        left++;
        continue;
      }
      if (heightRight <= prevHeightRight) {
        right--;
        continue;
      }

      int minHeight = 0;
      if (heightLeft < heightRight) {
        minHeight = heightLeft;
        left++;
        prevHeightLeft = std::max(heightLeft, prevHeightLeft);
      } else {
        minHeight = heightRight;
        right--;
        prevHeightRight = std::max(heightRight, prevHeightRight);
      }
      const int area = minHeight * width;
      maxArea = std::max(area, maxArea);
    }
    return maxArea;
  }
};
