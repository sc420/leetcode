class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    bool output = isMatchRange(s, p, 0, s.size() - 1, 0, p.size() - 1);
    if (hasRepeatedWildcards(p)) output = !output;
    return output;
  }

  bool hasRepeatedWildcards(const std::string &p) {
    char lastWildcardC = '\0';
    for (int i = 0; i < p.size(); i++) {
      const char c = p.at(i);
      if (c != '*') {
        if (isWildcard(p, i)) {
          if (c == lastWildcardC) return true;
          lastWildcardC = c;
        } else {
          lastWildcardC = '\0';
        }
      }
    }
    return false;
  }

  bool isMatchRange(const std::string &s, const std::string &p, const int sLeft,
                    const int sRight, const int pLeft, const int pRight) {
    // No input left. But any pattern left?
    if (sLeft > sRight) return isPatternAllWildcards(p, pLeft, pRight);
    if (pLeft > pRight) return false;  // Some characters can't be matched!

    const int sMid = (sLeft + sRight) / 2;
    const char c = s.at(sMid);
    for (int pIndex = pLeft; pIndex <= pRight; pIndex++) {
      if (p.at(pIndex) == c || p.at(pIndex) == '.') {
        bool leftMatch = false, rightMatch = false;
        if (isWildcard(p, pIndex)) {
          leftMatch = isMatchRange(s, p, sLeft, sMid - 1, pLeft, pIndex);
          rightMatch = isMatchRange(s, p, sMid + 1, sRight, pIndex, pRight);
        } else {
          leftMatch = isMatchRange(s, p, sLeft, sMid - 1, pLeft, pIndex - 1);
          rightMatch = isMatchRange(s, p, sMid + 1, sRight, pIndex + 1, pRight);
        }

        if (leftMatch && rightMatch) return true;
      }
    }

    return false;  // Some characters can't be matched!
  }

  bool isPatternAllWildcards(const std::string &p, const int pLeft,
                             const int pRight) {
    for (int pIndex = pLeft; pIndex <= pRight; pIndex++) {
      if (p.at(pIndex) != '*') {
        if (!isWildcard(p, pIndex)) return false;
      }
    }
    return true;
  }

  bool isWildcard(const std::string &p, const int pIndex) {
    if (pIndex + 1 < p.size() && p.at(pIndex + 1) == '*') return true;
    return false;
  }
};
