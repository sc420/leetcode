#include <cmath>

class Solution {
 public:
  std::string longestPalindrome(std::string s) {
    int skipDistance = 0;
    for (int center = 0; center <= maxIndex(s); center++) {
      // Check if the radius has been filled
      if (m_radii[center] > 0) continue;
      findLongestRadius(s, center, skipDistance);
      skipDistance = fillRightHandSide(s, center);
    }
    return findLongestSubstring(s);
  }

 private:
  void findLongestRadius(const std::string &s, const int center,
                         const int skipDistance = 0) {
    m_radii[center] = 1;  // Self
    m_radii[center] += skipDistance;
    int left = center - 1 - skipDistance;
    int right = center + 1 + skipDistance;
    const int minLeft = 0;
    const int maxRight = maxIndex(s);
    while (left >= minLeft && right <= maxRight &&
           getChar(s, left) == getChar(s, right)) {
      m_radii[center]++;
      left--;
      right++;
    }
  }

  int fillRightHandSide(const std::string &s, const int center) {
    int skipDistance = 0;
    int left = center - 1;
    int right = center + 1;
    const int minLeft = leftBound(center, m_radii[center]);
    const int maxRight = rightBound(center, m_radii[center]);
    while (left >= minLeft && right <= maxRight) {
      const int radiusOnLeft = m_radii[left];
      const int maxRadiusOnRight = calcRadius(right, maxRight);
      if (radiusOnLeft < maxRadiusOnRight) {
        // Case 1
        m_radii[right] = radiusOnLeft;
      } else if (radiusOnLeft > maxRadiusOnRight) {
        // Case 2
        m_radii[right] = maxRadiusOnRight;
      } else {
        // Case 3: skip this distance for the next step 1
        skipDistance = maxRadiusOnRight - 1;
        break;
      }
      left--;
      right++;
    }
    return skipDistance;
  }

  std::string findLongestSubstring(const std::string &s) {
    // Find center index with the max radius
    int maxRadius = 0;
    int center = -1;
    for (int i = 0; i <= maxIndex(s); i++) {
      if (m_radii[i] > maxRadius) {
        maxRadius = m_radii[i];
        center = i;
      }
    }
    // Produce the palindrome
    std::string substr;
    for (int i = leftBound(center, maxRadius);
         i <= rightBound(center, maxRadius); i++) {
      if (i % 2 != 0) substr += getChar(s, i);
    }
    return substr;
  }

  char getChar(const std::string &s, const int index) {
    if (index < 0 || index > maxIndex(s)) return '\0';
    if (index % 2 == 0) return '|';
    const int realIndex = index / 2;
    return s.at(realIndex);
  }

  int maxIndex(const std::string &s) { return 2 * s.size(); }

  int calcRadius(const int from, const int to) {
    return std::abs(to - from) + 1;
  }

  int leftBound(const int index, const int radius) {
    return index - radius + 1;
  }

  int rightBound(const int index, const int radius) {
    return index + radius - 1;
  }

 private:
  int m_radii[2 * 1000 + 1] = {0};
};
