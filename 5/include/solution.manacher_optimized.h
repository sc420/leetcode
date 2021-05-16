class Solution {
 public:
  std::string longestPalindrome(std::string s) {
    int radii[2 * 1000 + 1] = {0};
    int maxRad = 0, maxRadC = 0, maxRadRight = 1;
    for (int c = 0; c <= 2 * s.size(); c++) {
      if (radii[c] > 0) continue;
      radii[c] = maxRadRight;
      for (int l = c - radii[c]; nth(s, l) == nth(s, c + (c - l)); l--) {
        radii[c]++;
      }
      const int maxRight = c + radii[c] - 1;
      for (int l = c - 1; l >= c - radii[c] + 1; l--) {
        maxRadRight = maxRight - (c + (c - l)) + 1;
        if (radii[l] == maxRadRight) break;
        radii[c + (c - l)] = std::min(radii[l], maxRadRight);
      }
      if (radii[c] > maxRad) {
        maxRad = radii[c];
        maxRadC = c;
      }
    }
    return s.substr((maxRadC - maxRad + 1) / 2, (maxRad * 2 - 1) / 2);
  }

  char nth(const std::string &s, const int index) {
    if (index < 0) return '^';
    if (index > 2 * s.size()) return '$';
    if (index % 2 == 0) return '|';
    return s.at(index / 2);
  }
};
