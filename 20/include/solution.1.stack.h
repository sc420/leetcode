class Solution {
 public:
  bool isValid(std::string s) {
    std::stack<char> leftParens;
    for (int i = 0; i < s.size(); i++) {
      const char c = s.at(i);
      if (isLeftParen(c)) {
        leftParens.push(c);
      } else {
        if (leftParens.empty()) return false;
        const char prevC = leftParens.top();
        leftParens.pop();
        if (!isPair(prevC, c)) return false;
      }
    }
    return leftParens.empty();
  }

  bool isPair(const char c1, const char c2) {
    return (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') ||
           (c1 == '{' && c2 == '}');
  }

  bool isLeftParen(const char c) { return c == '(' || c == '[' || c == '{'; }
};
