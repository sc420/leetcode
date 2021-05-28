class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0) return false;
    return (long)x == reverse(x);
  }

  long reverse(int x) {
    long output = 0;
    while (x != 0) {
      const int digit = x % 10;
      output *= 10;
      output += digit;
      x /= 10;
    }
    return output;
  }
};
