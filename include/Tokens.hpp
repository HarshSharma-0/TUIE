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
namespace resolver {
void resolveView(const char *[], xmlNode *);
void resolveSText(const char *[], xmlNode *);
void resolveDText(const char *[], xmlNode *);
} // namespace resolver
namespace token {
constexpr uint64_t View = 0x5e4baa18;
constexpr uint64_t SText = 0x40d843a9;
constexpr uint64_t DText = 0xc2942574;
extern const char *vProp[];
extern const char *tProp[];
} // namespace token

namespace VIEW_PROP {
constexpr uint64_t BgColor = 0xe1d473c9;
constexpr uint64_t Border = 0xcad6f57;
constexpr uint64_t Padding = 0x736dd56;
constexpr uint64_t Margin = 0xc4cc799b;
constexpr uint64_t Touch = 0xf44fb78;
constexpr uint64_t id = 0x37386ae0;
} // namespace VIEW_PROP

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
