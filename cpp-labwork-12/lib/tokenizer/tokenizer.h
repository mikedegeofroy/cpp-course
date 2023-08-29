#include <cctype>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string& query) {
  std::vector<std::string> tokens;
  std::regex re(
      R"(\s*(==|!=|<=|>=|\+\+|--|\(|\)|,|<|>|=|!|\+|-|\*|/|;|'[^']*'|[^()\s,<>=!+\-*/;']+)\s*)");
  std::sregex_iterator it(query.begin(), query.end(), re);
  std::sregex_iterator end;

  while (it != end) {
    tokens.push_back(it->str(1));
    ++it;
  }

  return tokens;
}
