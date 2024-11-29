#ifndef __init_TUIE__
#define __init_TUIE__

#include <libxml2/libxml/parser.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <unordered_map>

class INIT_TUIE {
public:
  INIT_TUIE(char *);
  ~INIT_TUIE() = default;
  int INIT_RAW_MODE();
  int EXIT_RAW_MODE();

private:
  std::unordered_map<std::string, xmlDoc *> doc;
  struct termios org_setting;
  struct termios nterm_setting;
};
#endif // !DEBUG
