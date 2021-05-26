#include <climits>

class Solution {
 public:
  int myAtoi(std::string s) {
    int index = 0;
    while (runStep1(s, index /*may change*/))
      ;
    while (runStep2(s, index /*may change*/))
      ;
    while (runStep3(s, index /*may change*/))
      ;
    if (m_overflow) {
      return m_positive ? INT_MAX : INT_MIN;
    } else {
      return m_positive ? m_result : (-m_result);
    }
  }

  bool runStep1(const std::string &s, int &index) {
    if (index >= s.size()) return false;
    if (s.at(index) == ' ') {
      index++;
      return true;  // continue
    } else {
      return false;
    }
  }

  bool runStep2(const std::string &s, int &index) {
    if (index >= s.size()) return false;
    if (s.at(index) == '-') {
      m_positive = false;
      index++;
    } else if (s.at(index) == '+') {
      m_positive = true;
      index++;
    } else {
      m_positive = true;
    }
    return false;
  }

  bool runStep3(const std::string &s, int &index) {
    if (index >= s.size()) return false;
    if (s.at(index) >= '0' && s.at(index) <= '9') {
      const int digit = s.at(index) - '0';
      if (!safeMultiplyAndAdd(m_result, digit, m_result /*out*/))
        m_overflow = true;
      index++;
      return true;  // continue
    } else {
      return false;
    }
  }

  bool safeMultiplyAndAdd(const int a, const int x, int &out) {
    // Does a * 10 + x > INT_MAX ?
    // (Step 1) Does a * 10 > INT_MAX ?
    if (a > INT_MAX / 10) return false;
    // (Step 2) Does a * 10 + x > INT_MAX ?
    if (a * 10 > INT_MAX - x) return false;

    out = a * 10 + x;
    return true;
  }

  bool m_positive = false;
  bool m_overflow = false;
  int m_result = 0;
};
