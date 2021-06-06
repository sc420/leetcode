struct RomanAndValue {
  std::string romanStr;
  int value = 0;
};

class Solution {
 public:
  int romanToInt(std::string s) {
    static const RomanAndValue TABLE[] = {
        {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, {"C", 100},
        {"XC", 90},  {"L", 50},   {"XL", 40}, {"X", 10},   {"IX", 9},
        {"V", 5},    {"IV", 4},   {"I", 1},
    };

    int num = 0;
    for (const auto &item : TABLE) {
      while (s.substr(0, item.romanStr.length()) == item.romanStr) {
        num += item.value;
        s = s.substr(item.romanStr.length());
      }
    }
    return num;
  }
};
