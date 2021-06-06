struct RomanAndValue {
  std::string romanStr;
  int value = 0;
};

static const RomanAndValue TABLE[] = {
    {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, {"C", 100},
    {"XC", 90},  {"L", 50},   {"XL", 40}, {"X", 10},   {"IX", 9},
    {"V", 5},    {"IV", 4},   {"I", 1},
};

class Solution {
 public:
  std::string intToRoman(int num) {
    std::string roman;
    for (const auto &item : TABLE) {
      while (num >= item.value) {
        roman += item.romanStr;
        num -= item.value;
      }
    }
    return roman;
  }

  int romanToInt(std::string s) {
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
