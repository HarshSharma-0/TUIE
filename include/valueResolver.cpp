#include "Tokens.hpp"
#include "constantsVT00.hpp"
#include "libxml/xmlstring.h"
#include <cstdint>
#include <string>

void VALIDATOR::TOKEN::resolveViewValue(node *type, uint64_t &token,
                                        xmlChar *tmp) {
  switch (token) {
  case tagsToken::VIEW_PROP::id:
    type->id = (char *)xmlStrdup(tmp);
    break;
  case tagsToken::VIEW_PROP::BgColor:
    type->flagView->BgColor = (char *)xmlStrdup(tmp);
    break;
  case tagsToken::VIEW_PROP::Margin:
    type->flagView->margin = std::stoi((char *)tmp);
    break;
  case tagsToken::VIEW_PROP::Padding:
    type->flagView->padding = std::stoi((char *)tmp);
    break;
  case tagsToken::VIEW_PROP::Touch:

    break;
  case tagsToken::VIEW_PROP::flex:
    type->flagView->flex = std::stoi((char *)tmp);
    break;
  case tagsToken::VIEW_PROP::flextype:
    switch (tagsToken::generateFNVTOKEN((char *)tmp)) {
    case tagsToken::VALUE_VIEW::row:
      type->flagView->flextype = 1;
      break;
    default:
      type->flagView->flextype = 0;
      break;
    };
    break;
  case tagsToken::VIEW_PROP::alignItems:
    break;

  case tagsToken::VIEW_PROP::justifyContent:

    break;
  case tagsToken::VIEW_PROP::warp:
    type->flagView->warp = true;
    break;
  case tagsToken::VIEW_PROP::BorderCode:
    type->flagView->borderCode = (char *)xmlStrdup(tmp);
    break;
  };
};

void VALIDATOR::TOKEN::resolveTextValue(node *type, uint64_t &token,
                                        xmlChar *tmp, std::string &expand) {

  if (expand == "/") {
    expand = "\033[";
  }
  switch (token) {
  case tagsToken::TEXT_PROP::Color:
    expand += (char *)xmlStrdup(tmp);
    break;
  case tagsToken::TEXT_PROP::Bold:
    expand += BOLDTEXT;
    break;
  case tagsToken::TEXT_PROP::UnderLine:
    expand += UNDERLINETEXT;

    break;
  case tagsToken::TEXT_PROP::Dim:
    expand += DIMTEXT;
    break;
  case tagsToken::TEXT_PROP::Blink:
    expand += BLINKTEXT;
    break;
  case tagsToken::TEXT_PROP::Inverted:
    expand += INVERTEDTEXT;
    break;
  }
  expand += ";";
  return;
}
