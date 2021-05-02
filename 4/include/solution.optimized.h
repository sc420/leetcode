class Solution {
 public:
  double findMedianSortedArrays(std::vector<int> &nums1Vector,
                                std::vector<int> &nums2Vector) {
    const int *nums1 = nums1Vector.data();
    const int *nums2 = nums2Vector.data();

    int topLineIndex1 = -1;
    int topLineIndex2 = -1;
    const int m = (int)nums1Vector.size();
    const int n = (int)nums2Vector.size();
    int bottomLineIndex1 = m;
    int bottomLineIndex2 = n;

    int num1Top = (topLineIndex1 < 0
                       ? -1000001
                       : (topLineIndex1 >= m ? 1000001 : nums1[topLineIndex1]));
    int num2Top = (topLineIndex2 < 0
                       ? -1000001
                       : (topLineIndex2 >= n ? 1000001 : nums2[topLineIndex2]));
    int num1Bottom =
        (bottomLineIndex1 < 0
             ? -1000001
             : (bottomLineIndex1 >= m ? 1000001 : nums1[bottomLineIndex1]));
    int num2Bottom =
        (bottomLineIndex2 < 0
             ? -1000001
             : (bottomLineIndex2 >= n ? 1000001 : nums2[bottomLineIndex2]));
    while (topLineIndex1 < bottomLineIndex1 ||
           topLineIndex2 < bottomLineIndex2) {
      // Find the smallest number on the top line
      if (num1Top < num2Top) {
        topLineIndex1++;
        num1Top = (topLineIndex1 < 0
                       ? -1000001
                       : (topLineIndex1 >= m ? 1000001 : nums1[topLineIndex1]));
      } else {
        topLineIndex2++;
        num2Top = (topLineIndex2 < 0
                       ? -1000001
                       : (topLineIndex2 >= n ? 1000001 : nums2[topLineIndex2]));
      }

      // Find the biggest number on the bottom line
      if (num1Bottom > num2Bottom) {
        bottomLineIndex1--;
        num1Bottom =
            (bottomLineIndex1 < 0
                 ? -1000001
                 : (bottomLineIndex1 >= m ? 1000001 : nums1[bottomLineIndex1]));
      } else {
        bottomLineIndex2--;
        num2Bottom =
            (bottomLineIndex2 < 0
                 ? -1000001
                 : (bottomLineIndex2 >= n ? 1000001 : nums2[bottomLineIndex2]));
      }
    }

    const int smallestNumOnTopLine = (num1Top < num2Top) ? num1Top : num2Top;
    const int biggestNumOnBottomLine =
        (num1Bottom > num2Bottom) ? num1Bottom : num2Bottom;

    return (smallestNumOnTopLine + biggestNumOnBottomLine) / 2.0;
  }
};
