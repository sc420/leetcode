class Solution {
 public:
  int reverse(int x) {
    int output = 0;
    while (x != 0) {
      const int digit = x % 10;
      output *= 10;
      output += digit;
      x /= 10;
    }
    return output;
  }
};
