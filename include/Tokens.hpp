#ifndef __TOKEN_TUIE__
#define __TOKEN_TUIE__

#include "libxml/parser.h"
#include <cstdint>
#include <malloc.h>
#include <string>

#define __APP_ENTRY "app/home/home.xml"
#define __APP_ROOT ".local/TUIE"
#define __ERROR_FILE                                                           \
  "Error reading file or it not exist please check the respective path : "

namespace tagsToken {
uint64_t generateFNVTOKEN(const char *);

namespace token {
constexpr uint64_t View = 0x5e4baa18;
constexpr uint64_t Text = 0x40d843a9;
constexpr uint64_t TextInput = 0xd484cca2;
} // namespace token

namespace VIEW_PROP {
constexpr uint64_t id = 0x37386ae0;
constexpr uint64_t BgColor = 0xe1d473c9;
constexpr uint64_t Margin = 0xc4cc799b;
constexpr uint64_t Padding = 0x736dd56;
constexpr uint64_t Touch = 0xf44fb78;
constexpr uint64_t flex = 0xcae02ff2;
constexpr uint64_t flextype = 0xc79a9105;
constexpr uint64_t alignItems = 0xb4ee9bca;
constexpr uint64_t justifyContent = 0x6538bb8;
constexpr uint64_t warp = 0x8efa7aaf;
constexpr uint64_t BorderCode = 0x2c625d6;

} // namespace VIEW_PROP
namespace VALUE_VIEW {
constexpr uint64_t row = 0x440e1d7b;
constexpr uint64_t center = 0x58c4484;
constexpr uint64_t spaceBetween = 0x8d57d378;
constexpr uint64_t spaceAround = 0xd21f93d1;
constexpr uint64_t flexEnd = 0x34a91f2;
constexpr uint64_t flexStart = 0x9b778b97;
}; // namespace VALUE_VIEW
namespace TEXT_PROP {
constexpr uint64_t Color = 0xe5b43cf8;
constexpr uint64_t Bold = 0x45768d96;
constexpr uint64_t UnderLine = 0x312b00ff;
constexpr uint64_t Dim = 0x35691dd9;
constexpr uint64_t Blink = 0xdbd66129;
constexpr uint64_t Inverted = 0xe349e958;
constexpr uint64_t id = 0x37386ae0;
} // namespace TEXT_PROP
} // namespace tagsToken

struct configView {
  int flex{0};
  char *BgColor{nullptr};
  char *borderCode{nullptr};
  int margin{0};
  int padding{0};
  bool touch{false};
  bool warp{false};
  int flextype{0};
  int alignItems{0};
  int justifyContent{0};
};
struct Text {
  char *color{nullptr};
  char *textBlob{nullptr};
  bool isGrad{false};
  int len{0};
};

class node {
public:
  uint64_t ltoken{0};
  char *id{nullptr}; // if nullptr then notupdatable
  node *next{nullptr};
  node *prev{nullptr};
  node *child{nullptr};
  struct configView *flagView{nullptr};
  struct Text *flagText{nullptr};
  int height{0};
  int width{0};
  ~node();
};

namespace VALIDATOR {
void freeNode(node *);
class TOKEN {
public:
  node *getNextNode(xmlNode *);
  bool validateRoot(xmlNode *);
  void resolveProp(xmlNode *, const char *[], node *);

private:
  void resolveViewValue(node *, uint64_t &, xmlChar *);
  void resolveTextValue(node *, uint64_t &, xmlChar *, std::string &);

  const char *viewProp[12] = {"id",        "BgColor",    "Margin",
                              "Padding",   "Touch",      "flex",
                              "flex-type", "alignItems", "justifyContent",
                              "warp",      "BorderCode", nullptr};
  const char *TextProp[8] = {"Color", "Bold",     "Underline", "Dim",
                             "Blink", "Inverted", "id",        nullptr};
  const char *rootTag = "TUIEngine";
};
}; // namespace VALIDATOR

#endif // !__TOKEN_TUIE__
