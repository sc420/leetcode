class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    std::cout << "--------------------------------------------------\n";
    return isMatchRange(s, p, 0, s.size() - 1, 0, p.size() - 1);
  }

  bool isMatchRange(const std::string &s, const std::string &p, const int sLeft,
                    const int sRight, const int pLeft, const int pRight) {
    if (sLeft > sRight) return true;   // No input left
    if (pLeft > pRight) return false;  // Some characters can't be matched!

    std::cout << '\n';
    std::cout << "s = \"" << s.substr(sLeft, sRight - sLeft + 1) << "\"\n";
    std::cout << "sRange = [" << sLeft << ", " << sRight << "]\n";
    std::cout << "p = \"" << p.substr(pLeft, pRight - pLeft + 1) << "\"\n";
    std::cout << "pRange = [" << pLeft << ", " << pRight << "]\n";

    const int sMid = (sLeft + sRight) / 2;
    const char c = s.at(sMid);

    std::cout << "Finding s[" << sMid << "] = '" << c << "' in p\n";

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

        if (leftMatch && rightMatch) {
          std::cout << "Both left and right part match! pIndex = " << pIndex
                    << '\n';
          return true;
        }
      }
    }

    std::cout << "Couldn't find anything in p\n";

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
