class Solution {
 public:
  double findMedianSortedArrays(std::vector<int> &nums1,
                                std::vector<int> &nums2) {
    int topLineIndex1 = -1;
    int topLineIndex2 = -1;
    int bottomLineIndex1 = (int)nums1.size();
    int bottomLineIndex2 = (int)nums2.size();

    while (topLineIndex1 < bottomLineIndex1 ||
           topLineIndex2 < bottomLineIndex2) {
      const int num1Top = _getArrayNum(nums1, topLineIndex1);
      const int num2Top = _getArrayNum(nums2, topLineIndex2);
      const int num1Bottom = _getArrayNum(nums1, bottomLineIndex1);
      const int num2Bottom = _getArrayNum(nums2, bottomLineIndex2);

      // Find the smallest number on the top line
      if (num1Top < num2Top) {
        topLineIndex1++;
      } else {
        topLineIndex2++;
      }

      // Find the biggest number on the bottom line
      if (num1Bottom > num2Bottom) {
        bottomLineIndex1--;
      } else {
        bottomLineIndex2--;
      }
    }

    const int num1Top = _getArrayNum(nums1, topLineIndex1);
    const int num2Top = _getArrayNum(nums2, topLineIndex2);
    const int num1Bottom = _getArrayNum(nums1, bottomLineIndex1);
    const int num2Bottom = _getArrayNum(nums2, bottomLineIndex2);

    const int smallestNumOnTopLine = (num1Top < num2Top) ? num1Top : num2Top;
    const int biggestNumOnBottomLine =
        (num1Bottom > num2Bottom) ? num1Bottom : num2Bottom;

    return (smallestNumOnTopLine + biggestNumOnBottomLine) / 2.0;
  }

 private:
  int _getArrayNum(const std::vector<int> &nums, const int index) {
    if (index < 0) return -1000001;
    if (index >= (int)nums.size()) return 1000001;
    return nums.at(index);
  }
};
