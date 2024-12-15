#include "Tokens.hpp"
#include "init.hpp"
#include "iostream"
#include "parser.hpp"
#include "renderer.hpp"

int main() {
  INIT_TUIE INIT((char *)"fist");
  OPEN_APP OPEN;
  renderer SCREEN;
  int proceed = OPEN.parser(INIT.appPath);
  if (proceed == -1) {
    std::cout << __ERROR_FILE << INIT.appPath << std::endl;
  }
  SCREEN.setNode(OPEN.renderNodes);
  OPEN.parserCleanXml();
  OPEN.parserClean();
  return 0;
}
