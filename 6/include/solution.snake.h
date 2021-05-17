class Solution {
 public:
  std::string convert(std::string s, int numRows) {
    if (numRows <= 1) return s;
    const int numCols = s.size() / (numRows - 1) + 1;
    std::string output;
    for (int r = 0; r < numRows; r++) {
      for (int c = 0; c < numCols; c++) {
        const int snakeIndex = getSnakeIndex(r, c, numRows);
        const char ch = getChar(s, snakeIndex, numRows);
        if (ch != '\0') output += ch;
      }
    }
    return output;
  }

 private:
  char getChar(const std::string &s, const int snakeIndex, const int numRows) {
    if (snakeIndex == 0) return s.at(0);
    if (snakeIndex % numRows == 0) return '\0';
    const int numEmpty = snakeIndex / numRows;
    const int realIndex = snakeIndex - numEmpty;
    if (realIndex >= s.size()) return '\0';
    return s.at(realIndex);
  }

  int getSnakeIndex(const int r, const int c, const int numRows) {
    const int baseIndex = c * numRows;
    if (c % 2 == 0) {
      // Downward
      return baseIndex + r;
    } else {
      // Upward
      return baseIndex + (numRows - 1 - r);
    }
  }
};
