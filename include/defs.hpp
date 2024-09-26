#ifndef DEFS_H
#define DEFS_H

#include "libxml/xmlstring.h"

namespace RenderTypes {

constexpr int ENGINE_MODULE = 0;
constexpr int ENGINE_VIEW = 1;
constexpr int ENGINE_SCROLLVIEW = 2;
constexpr int ENGINE_TEXT = 3;
constexpr int ENGINE_TOUCHABLE = 4;
constexpr int ENGINE_PROGRESS = 5;
constexpr int ENGINE_ICON = 6;
constexpr int ENGINE_MODULE_DEFINE = 7;

constexpr int JUSTIFY_CENTER = 0;
constexpr int JUSTIFY_FLEX_START = 1;
constexpr int JUSTIFY_FLEX_END = 2;
constexpr int JUSTIFY_SPACE_BETWEEN = 3;
constexpr int JUSTIFY_SPACE_AROUND = 4;

constexpr int FLEX_DIRECTION_ROW = 0;
constexpr int FLEX_DIRECTION_COL = 1;

constexpr int VIEW_ID = 0;
constexpr int VIEW_FLEX = 1;
constexpr int VIEW_JUSTIFY_CONTENT = 2;
constexpr int VIEW_ALIGN_SELF = 3;
constexpr int VIEW_BACKGROUND_COLOR = 4;
constexpr int VIEW_MARGIN_PADDING = 5;
constexpr int VIEW_PADDING = 6;
constexpr int VIEW_POSITION = 7;

} // namespace RenderTypes

extern const xmlChar *predefinedRenderMap[];
extern const xmlChar *predefinedAlignAttributes[];
extern const xmlChar *predefinedGlobalMap[];
extern const xmlChar *tagProp[];
extern const xmlChar *predefinedRootTag;
extern const char *rootFileName;

#endif
