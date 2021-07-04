class Solution {
 public:
  bool isValid(std::string s) {
    std::string newS = s;
    do {
      s = newS;
      newS = eat(s);
    } while (newS != s);
    return newS == "";
  }

  std::string eat(const std::string &s) {
    if (s.size() < 2) return s;
    const char leftChar = s.at(0);
    const char rightChar = s.at(1);
    if (!isLeftParen(leftChar)) return s;
    if (isRightParen(rightChar) && !isPair(leftChar, rightChar)) return s;
    if (isPair(leftChar, rightChar)) {
      return s.substr(2, s.size() - 2);
    } else {
      const std::string headlessS = s.substr(1, s.size() - 1);
      const std::string newS = eat(headlessS);
      return s.substr(0, 1) + newS;
    }
  }

  bool isPair(const char c1, const char c2) {
    return (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') ||
           (c1 == '{' && c2 == '}');
  }

  bool isLeftParen(const char c) { return c == '(' || c == '[' || c == '{'; }

  bool isRightParen(const char c) { return c == ')' || c == ']' || c == '}'; }
};
