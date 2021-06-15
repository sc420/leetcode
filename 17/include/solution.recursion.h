class Solution {
 public:
  std::vector<std::string> letterCombinations(std::string digits) {
    std::vector<std::string> output;
    appendLetter(digits, 0, "", output /*will change*/);
    return output;
  }

  void appendLetter(const std::string &digits, const int digitIndex,
                    const std::string &s, std::vector<std::string> &output) {
    if (digitIndex >= digits.length()) {
      if (s != "") output.push_back(s);
      return;
    }

    const int wordIndex = digits.at(digitIndex) - '2';
    const std::string &word = m_wordList.at(wordIndex);
    for (const char c : word) {
      const std::string newS = s + c;
      appendLetter(digits, digitIndex + 1, newS, output /*will change*/);
    }
  }

  const std::vector<std::string> m_wordList = {
      "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz",
  };
};
