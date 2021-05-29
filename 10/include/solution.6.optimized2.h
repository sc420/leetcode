// Reference: https://zxi.mytechroad.com/blog/searching/leetcode-10-regular-expression-matching/
class Solution {
public:
  bool isMatch(string s, string p) {
    const string optimizedP = optimizePattern(p);
    return isMatch(s.c_str(), optimizedP.c_str());
  }
private:
  bool isMatch(const char* s, const char* p) {
    if (*p == '\0') return *s == '\0';
        
    // normal case, e.g. 'a.b','aaa', 'a'
    if (p[1] != '*' || p[1] == '\0') {
      // no char to match
      if (*s == '\0') return false;
 
      if (*s == *p || *p == '.')
        return isMatch(s + 1, p + 1);
      else
        return false;
    }
    else {
      int i = -1;
      while (i == -1 || s[i] == p[0] || p[0] == '.') {
          if (isMatch(s + i + 1, p + 2)) return true;
          if (s[++i] == '\0') break;
      }
      return false;
    }
    
    return false;
  }

  std::string optimizePattern(const std::string &p) {
    std::string optimizedP;
    int pIndex = 0;
    while (pIndex < p.size()) {
      // e.g., "a*a*"
      //          ^
      if (pIndex < p.size() - 1 && p.at(pIndex + 1) == '*' && pIndex >= 2) {
        const int prevPIndex = pIndex - 2;
        if (p.substr(prevPIndex, 2) == p.substr(pIndex, 2)) {
          pIndex += 2;
          continue;
        }
      }
      optimizedP += p.at(pIndex);
      pIndex++;
    }
    return optimizedP;
  }
};
