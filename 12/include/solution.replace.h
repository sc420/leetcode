class Solution {
 public:
  std::string intToRoman(int num) {
    const int digit1000 = ((num % 10000) / 1000);
    const int digit100 = ((num % 1000) / 100);
    const int digit10 = ((num % 100) / 10);
    const int digit1 = ((num % 10) / 1);
    return digitToRoman1000(digit1000) + digitToRoman100(digit100) +
           digitToRoman10(digit10) + digitToRoman1(digit1);
  }

  std::string digitToRoman1000(const int digit) {
    static const char *TABLE[] = {"", "M", "MM", "MMM", "",
                                  "", "",  "",   "",    ""};
    return TABLE[digit];
  }

  std::string digitToRoman100(const int digit) {
    static const char *TABLE[] = {"",  "C",  "CC",  "CCC",  "CD",
                                  "D", "DC", "DCC", "DCCC", "CM"};
    return TABLE[digit];
  }

  std::string digitToRoman10(const int digit) {
    static const char *TABLE[] = {"",  "X",  "XX",  "XXX",  "XL",
                                  "L", "LX", "LXX", "LXXX", "XC"};
    return TABLE[digit];
  }

  std::string digitToRoman1(const int digit) {
    static const char *TABLE[] = {"",  "I",  "II",  "III",  "IV",
                                  "V", "VI", "VII", "VIII", "IX"};
    return TABLE[digit];
  }
};
