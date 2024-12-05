#include "init.hpp"
#include "parser.hpp"

int main() {
  INIT_TUIE INIT((char *)"fist");
  OPEN_APP OPEN;
  if (OPEN.parser(INIT.appPath) == -1) {
    return -1;
  }

  return 0;
}
