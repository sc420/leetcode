#include <algorithm>

class Solution {
 public:
  std::string longestCommonPrefix(std::vector<std::string> &strs) {
    const std::string &firstStr = strs.front();
    const size_t minLength = getMinLength(strs);
    for (size_t i = 0; i < minLength; i++) {
      const char c = firstStr.at(i);
      for (size_t otherIndex = 1; otherIndex < strs.size(); otherIndex++) {
        const std::string &otherStr = strs.at(otherIndex);
        if (otherStr.at(i) != c) {
          return firstStr.substr(0, i);
        }
      }
    }
    return firstStr.substr(0, minLength);
  }

  size_t getMinLength(const std::vector<std::string> &strs) {
    size_t minLength = 200;
    for (const auto &str : strs) {
      minLength = std::min(str.length(), minLength);
    }
    return minLength;
  }
};
