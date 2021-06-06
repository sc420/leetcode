class Solution {
 public:
  int romanToInt(std::string s) {
    int num = 0;

    for (int digit = 9; digit >= 0; digit--) {
      const std::string prefix = digitToRoman1000(digit);
      if (startsWith(s, prefix)) {
        num += 1000 * digit;
        s = s.substr(prefix.length());
        break;
      }
    }
    for (int digit = 9; digit >= 0; digit--) {
      const std::string prefix = digitToRoman100(digit);
      if (startsWith(s, prefix)) {
        num += 100 * digit;
        s = s.substr(prefix.length());
        break;
      }
    }
    for (int digit = 9; digit >= 0; digit--) {
      const std::string prefix = digitToRoman10(digit);
      if (startsWith(s, prefix)) {
        num += 10 * digit;
        s = s.substr(prefix.length());
        break;
      }
    }
    for (int digit = 9; digit >= 0; digit--) {
      const std::string prefix = digitToRoman1(digit);
      if (startsWith(s, prefix)) {
        num += 1 * digit;
        s = s.substr(prefix.length());
        break;
      }
    }

    return num;
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

  bool startsWith(const std::string &s, const std::string &prefix) {
    if (prefix == "") return false;
    return s.substr(0, prefix.length()) == prefix;
  }
};
