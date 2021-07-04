class Solution {
 public:
  bool isValid(std::string s) {
    int leftIndex = 0, rightIndex = 1, nextIndex = 0;
    while (leftIndex < s.size()) {
      if (!eat(s, leftIndex, rightIndex, nextIndex /*change*/)) return false;
      leftIndex = nextIndex;
      rightIndex = leftIndex + 1;
    }
    return true;
  }

  bool eat(const std::string &s, const int leftIndex, const int rightIndex,
           int &nextIndex /*change*/) {
    if (leftIndex >= s.size() || rightIndex >= s.size()) return false;
    const char leftChar = s.at(leftIndex);
    const char rightChar = s.at(rightIndex);
    if (!isLeftParen(leftChar)) return false;
    if (isRightParen(rightChar) && !isPair(leftChar, rightChar)) return false;
    if (isPair(leftChar, rightChar)) {
      nextIndex = rightIndex + 1;
      return true;
    } else {
      if (!eat(s, rightIndex, rightIndex + 1, nextIndex /*change*/))
        return false;
      return eat(s, leftIndex, nextIndex, nextIndex /*change*/);
    }
  }

  bool isPair(const char c1, const char c2) {
    return (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') ||
           (c1 == '{' && c2 == '}');
  }

  bool isLeftParen(const char c) { return c == '(' || c == '[' || c == '{'; }

  bool isRightParen(const char c) { return c == ')' || c == ']' || c == '}'; }
};
