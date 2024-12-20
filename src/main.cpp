#include "Tokens.hpp"
#include "init.hpp"
#include "iostream"
#include "parser.hpp"
#include "renderer.hpp"

int main() {
  INIT_TUIE INIT((char *)"myapp");
  OPEN_APP OPEN;
  renderer SCREEN;
  int proceed = OPEN.parser(INIT.appPath);
  INIT.INIT_RAW_MODE();
  if (proceed == -1) {
    std::cout << __ERROR_FILE << INIT.appPath << std::endl;
    INIT.EXIT_RAW_MODE();
    return -1;
  }
  SCREEN.initRenderer(OPEN.renderNodes);
  OPEN.parserCleanXml();
  OPEN.parserClean();
  INIT.EXIT_RAW_MODE();
  return 0;
}
