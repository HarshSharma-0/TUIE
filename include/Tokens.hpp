#ifndef __TOKEN_TUIE__
#define __TOKEN_TUIE__

#include "libxml/parser.h"
#include <cstdint>
#define __APP_ENTRY "app/home/home.xml"
#define __APP_ROOT ".local/TUIE"
#define __ERROR_FILE                                                           \
  "Error reading file or it not exist please check the respective path : "

namespace tagsToken {
uint64_t generateFNVTOKEN(const char *);

namespace token {
extern uint64_t VIEW;
extern uint64_t STEXT;
extern uint64_t DTEXT;
}; // namespace token
}; // namespace tagsToken

class node {
public:
  uint64_t ltoken{0};
  char *id{nullptr};
  node *next{nullptr};
  node *prev{nullptr};
  node *child{nullptr};
};

namespace VALIDATOR {
class TOKEN {
public:
  node *getNextNode(xmlNode *);
  bool validateRoot(xmlNode *);

private:
  const char *xmlTags[3] = {"View", "STEXT", "DTEXT"};
  const char *rootTag = "TUIEngine";
};
}; // namespace VALIDATOR

#endif // !__TOKEN_TUIE__
