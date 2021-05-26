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
    if (!m_positive) m_result *= -1;
    return m_result;
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
      m_result *= 10;
      m_result += digit;
      index++;
      return true;  // continue
    } else {
      return false;
    }
  }

  bool m_positive = false;
  int m_result = 0;
};
