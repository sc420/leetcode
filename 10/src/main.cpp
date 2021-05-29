#include <iostream>
#include <string>
#include <vector>

#include "solution.3.fixed.h"

struct Problem {
  std::string s;
  std::string p;
  bool expectedOutput = false;
};

static const std::vector<Problem> problems = {
    {"aa", "a", false},
    {"aa", "a*", true},
    {"ab", ".*", true},
    {"aab", "c*a*b", true},
    {"mississippi", "mis*is*p*.", false},
    {"mississippi", "mis*is*ip*.", true},
    {"mississippi", "mis*is*.p*.", true},
    {"mississippi", ".*s*is*.p*.", true},
    {"mississippi", ".*is*.p*.", true},
    {"mississippi", ".*.p*.", true},
    {"mississippi", "..*.p*.", true},
    // Added after submitted the "1.bug" version
    {"ab", ".*c", false},
    // Added after submitted the "4.check_repeated" version
    {"aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*a*a*b", true},
};

bool validateOutput(const bool output, const Problem &problem) {
  return output == problem.expectedOutput;
}

int main(int argc, char *argv[]) {
  for (const Problem &problem : problems) {
    Solution solution;
    const double output = solution.isMatch(problem.s, problem.p);
    if (!validateOutput(output, problem)) {
      std::cout << "Wrong Answer\n";
      std::cout << "problem.s = " << problem.s << '\n';
      std::cout << "problem.p = " << problem.p << '\n';
      std::cout << "problem.expectedOutput = " << problem.expectedOutput
                << '\n';
      std::cout << "solution.isMatch(s, p) = " << output << '\n';
      return 1;
    }
  }

  std::cout << "Accepted\n";
  return 0;
}
