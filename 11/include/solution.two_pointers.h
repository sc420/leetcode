#include <algorithm>

class Solution {
 public:
  int maxArea(std::vector<int> &height) {
    int maxArea = 0;
    int left = 0;
    int right = height.size() - 1;
    while (left < right) {
      const int width = right - left;
      const int heightLeft = height.at(left);
      const int heightRight = height.at(right);
      int minHeight = 0;
      if (heightLeft < heightRight) {
        minHeight = heightLeft;
        left++;
      } else {
        minHeight = heightRight;
        right--;
      }
      const int area = minHeight * width;
      maxArea = std::max(area, maxArea);
    }
    return maxArea;
  }
};
