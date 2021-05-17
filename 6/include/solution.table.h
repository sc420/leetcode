#include <algorithm>

class Solution {
 public:
  std::string convert(std::string s, int numRows) {
    if (numRows == 1) return s;
    const int numColumns = calcNumColumns(s, numRows);
    std::string output(numRows * numColumns, '*');
    int row = 0, col = 0;
    bool goingDown = true;
    for (const char c : s) {
      const int index = row * numColumns + col;
      output[index] = c;

      row += (goingDown ? 1 : -1);
      col += (goingDown ? 0 : 1);
      if (row == 0) goingDown = true;
      if (row == numRows - 1) goingDown = false;
    }
    output.erase(std::remove(output.begin(), output.end(), '*'), output.end());
    return output;
  }

 private:
  int calcNumColumns(const std::string &s, const int numRows) {
    const int len = (int)s.size();
    const int groupSize = 2 * (numRows - 1);
    const int groupWidth = numRows - 1;
    const int numGroups = len / groupSize;
    const int remainder = len % groupSize;
    int lastGroupSize = 0;
    if (remainder > 0 && remainder <= numRows) {
      lastGroupSize = 1;
    } else if (remainder > numRows) {
      lastGroupSize = 1 + (remainder - numRows);
    }
    return numGroups * groupWidth + lastGroupSize;
  }
};
