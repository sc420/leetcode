class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    return isMatchRange(s, p, 0, s.size() - 1, 0, p.size() - 1);
  }

  bool isMatchRange(const std::string &s, const std::string &p, const int sLeft,
                    const int sRight, const int pLeft, const int pRight) {
    if (sLeft > sRight) return true;   // No input left
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

    // Is everything wildcard so it's okay we couldn't find anything?
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
