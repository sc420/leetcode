#include <climits>

class Solution {
 public:
  int reverse(int x) {
    int output = 0;
    while (x != 0) {
      const int digit = x % 10;
      if (!safeMultiplyAndAdd(output, digit, output /*out*/)) return 0;
      x /= 10;
    }
    return output;
  }

  bool safeMultiplyAndAdd(const int a, const int x, int &out) {
    if (x > 0) {
      // Does a * 10 + x > INT_MAX ?
      // (Step 1) Does a * 10 > INT_MAX ?
      if (a > INT_MAX / 10) return false;
      // (Step 2) Does a * 10 + x > INT_MAX ?
      if (a * 10 > INT_MAX - x) return false;
    } else {
      // Does a * 10 + x < INT_MIN ?
      // (Step 1) Does a * 10 < INT_MIN ?
      if (a < INT_MIN / 10) return false;
      // (Step 2) Does a * 10 + x < INT_MIN ?
      if (a * 10 < INT_MIN - x) return false;
    }

    out = a * 10 + x;
    return true;
  }
};
