class Solution {
 public:
  std::string longestCommonPrefix(std::vector<std::string> &strs) {
    const std::string &firstStr = strs.at(0);
    for (size_t i = 0; i < firstStr.length(); i++) {
      const char c = firstStr.at(i);
      for (size_t otherIndex = 1; otherIndex < strs.size(); otherIndex++) {
        const std::string &otherStr = strs.at(otherIndex);
        if (i >= otherStr.size() || otherStr.at(i) != c) {
          return firstStr.substr(0, i);
        }
      }
    }
    return firstStr;
  }
};
