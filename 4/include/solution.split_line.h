#include <algorithm>

class Solution {
 public:
  double findMedianSortedArrays(std::vector<int> &nums1,
                                std::vector<int> &nums2) {
    const int n1Size = (int)nums1.size();
    const int n2Size = (int)nums2.size();
    int start = 0;
    int end = n1Size;

    while (start <= end) {
      const int leftCutIndex = (start + end) / 2;
      const int rightCutIndex = _rightCutIndex(leftCutIndex, n1Size, n2Size);

      const int upperLeftNum = _getNth(nums1, leftCutIndex - 1);
      const int lowerLeftNum = _getNth(nums1, leftCutIndex);
      const int upperRightNum = _getNth(nums2, rightCutIndex - 1);
      const int lowerRightNum = _getNth(nums2, rightCutIndex);

      if (upperLeftNum > lowerRightNum) {
        end = leftCutIndex;
      } else if (lowerLeftNum < upperRightNum) {
        start = leftCutIndex + 1;
      } else {
        m_upperMax = std::max(upperLeftNum, upperRightNum);
        m_lowerMin = std::min(lowerLeftNum, lowerRightNum);
        break;
      }
    }

    if ((n1Size + n2Size) % 2 == 0) {
      return (m_upperMax + m_lowerMin) / 2.0;
    } else {
      return m_lowerMin;
    }
  }

 private:
  int _getNth(const std::vector<int> &nums, const int index) {
    if (index < 0) return -1000001;
    if (index >= (int)nums.size()) return 1000001;
    return nums.at(index);
  }

  int _rightCutIndex(const int leftCutIndex, const int n1Size,
                     const int n2Size) {
    const int fakeN1Size = n1Size + 2;
    const int fakeN2Size = n2Size + 2;
    const int totalFake = fakeN1Size + fakeN2Size;

    const int numUpper = totalFake / 2;
    const int numUpperLeft = leftCutIndex + 1;
    const int numUpperRight = numUpper - numUpperLeft;
    return numUpperRight - 1;
  }

 private:
  int m_upperMax = 0;
  int m_lowerMin = 0;
};
