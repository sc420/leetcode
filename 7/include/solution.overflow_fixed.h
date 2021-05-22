#include <climits>

class Solution {
 public:
  int reverse(int x) {
    int output = 0;
    while (x != 0) {
      const int digit = x % 10;
      if (!safeMultiply(output, 10, output /*out*/)) return 0;
      if (!safeAdd(output, digit, output /*out*/)) return 0;
      x /= 10;
    }
    return output;
  }

  bool safeMultiply(const int a, const int x, int &out) {
    // Does a * x > INT_MAX ?
    if (a > INT_MAX / x) return false;
    // Does a * x < INT_MIN ?
    if (a < INT_MIN / x) return false;
    out = a * x;
    return true;
  }

  bool safeAdd(const int a, const int x, int &out) {
    // Does a + x > INT_MAX ?
    if (x > 0 && a > INT_MAX - x) return false;
    // Does a + x < INT_MIN ?
    if (x < 0 && a < INT_MIN - x) return false;
    out = a + x;
    return true;
  }
};
