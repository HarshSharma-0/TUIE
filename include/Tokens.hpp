#ifndef __TOKEN_TUIE__
#define __TOKEN_TUIE__

#define __APP_ENTRY "app/home/home.xml"
#define __APP_ROOT ".local/TUIE"
#define __ERROR_FILE                                                           \
  "Error reading file or it not exist please check the respective path :"

struct tagsToken {
  enum class tags {
    VIEW_TOKEN,
    STEXT_TOKEN,
    DTEXT_TOKEN,
  };
};

class node {
  tagsToken::tags ltoken;
  char *id{nullptr};
  node *next{nullptr};
  node *prev{nullptr};
  node *child{nullptr};
  ~node();
  node(char *);
};

namespace VALIDATOR {
class TOKEN {
public:
private:
  const char *xmlTags[4] = {"View", "STEXT", "DTEXT", nullptr};
};
}; // namespace VALIDATOR

#endif // !__TOKEN_TUIE__
