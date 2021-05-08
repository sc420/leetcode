#include <vector>

class Solution {
 public:
  std::string longestPalindrome(std::string s) {
    std::vector<int> compareList;
    for (size_t index = 0; index < s.size(); index++) {
      const char curChar = getChar(s, index);
      std::vector<int> newCompareList;

      // Check if the single character palindrome is longer
      checkLongerPalindrome(s, index, index);

      // Check previous positions
      for (const int compareIndex : compareList) {
        if (curChar == getChar(s, compareIndex)) {
          checkLongerPalindrome(s, compareIndex, index);
          newCompareList.push_back(compareIndex - 1);
        }
      }

      // Check i-1 position
      // For example: aa
      //               ^ index
      if (curChar == getChar(s, index - 1)) {
        checkLongerPalindrome(s, index - 1, index);
        newCompareList.push_back(index - 2);
      }

      // Check i-2 position
      // For example: aba
      //                ^ index
      if (curChar == getChar(s, index - 2)) {
        checkLongerPalindrome(s, index - 2, index);
        newCompareList.push_back(index - 3);
      }

      compareList = newCompareList;
    }
    return m_longestPalindrome;
  }

 private:
  char getChar(const std::string &s, const int pos) {
    if (pos < 0 || pos > (int)s.size()) return '\0';
    return s.at(pos);
  }

  void checkLongerPalindrome(const std::string &s, const int startPos,
                             const int endPos) {
    const int length = endPos - startPos + 1;
    if (length > (int)m_longestPalindrome.size()) {
      m_longestPalindrome = s.substr(startPos, length);
    }
  }

 private:
  std::string m_longestPalindrome = "";
};
