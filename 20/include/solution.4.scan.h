class Solution {
 public:
  bool isValid(std::string s) {
    while (eat(s))
      ;
    for (const char c : s) {
      if (c != ' ') return false;
    }
    return true;
  }

  bool eat(std::string &s) {
    bool hasEat = false;
    int prevIndex = 0;
    for (int i = 0; i < s.size(); i++) {
      const char c = s.at(i);
      if (c == ' ') continue;
      const char prevC = s.at(prevIndex);
      if (isPair(prevC, c)) {
        s[prevIndex] = ' ';
        s[i] = ' ';
        hasEat = true;
      }
      prevIndex = i;
    }
    return hasEat;
  }

  bool isPair(const char c1, const char c2) {
    return (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') ||
           (c1 == '{' && c2 == '}');
  }
};
