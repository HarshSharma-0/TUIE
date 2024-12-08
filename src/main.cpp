#include "Tokens.hpp"
#include "init.hpp"
#include "iostream"
#include "parser.hpp"

int main() {
  INIT_TUIE INIT((char *)"fist");
  OPEN_APP OPEN;
  int proceed = OPEN.parser(INIT.appPath);
  switch (proceed) {
  case -1:
    std::cout << __ERROR_FILE << INIT.appPath << std::endl;
    return -1;
  case -2:
    std::cout << "parser error" << std::endl;
    break;
  case -3:
    break;
    break;
  default:

    break;
  }

  return 0;
}
