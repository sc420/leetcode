struct RomanAndValue {
  std::string romanStr;
  int value = 0;
};

class Solution {
 public:
  std::string intToRoman(int num) {
    static const RomanAndValue TABLE[] = {
        {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400}, {"C", 100},
        {"XC", 90},  {"L", 50},   {"XL", 40}, {"X", 10},   {"IX", 9},
        {"V", 5},    {"IV", 4},   {"I", 1},
    };

    std::string roman;
    for (const auto &item : TABLE) {
      while (num >= item.value) {
        roman += item.romanStr;
        num -= item.value;
      }
    }
    return roman;
  }
};
