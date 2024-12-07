#include "Tokens.hpp"
#include "init.hpp"
#include "iostream"
#include "parser.hpp"

int main() {
  INIT_TUIE INIT((char *)"fist");
  OPEN_APP OPEN;
  if (OPEN.parser(INIT.appPath) == -1) {
    std::cout << __ERROR_FILE << INIT.appPath << std::endl;
    return -1;
  }

  return 0;
}
