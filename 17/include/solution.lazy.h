class Solution {
 public:
  std::vector<std::string> letterCombinations(std::string digits) {
    std::vector<std::string> words;
    for (const char digit : digits)
      words.push_back(m_wordList.at(digit - '2'));
    while (words.size() < 4) words.push_back(" ");

    std::vector<std::string> output;
    for (size_t i1 = 0; i1 < words[0].length(); i1++) {
      for (size_t i2 = 0; i2 < words[1].length(); i2++) {
        for (size_t i3 = 0; i3 < words[2].length(); i3++) {
          for (size_t i4 = 0; i4 < words[3].length(); i4++) {
            std::string s = words[0].substr(i1, 1) + words[1].substr(i2, 1) +
                            words[2].substr(i3, 1) + words[3].substr(i4, 1);
            s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
            if (s != "") output.push_back(s);
          }
        }
      }
    }
    return output;
  }

  const std::vector<std::string> m_wordList = {
      "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz",
  };
};
