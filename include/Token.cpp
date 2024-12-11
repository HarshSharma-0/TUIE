#include "Tokens.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <cstdint>
#include <iostream>

node *VALIDATOR::TOKEN::getNextNode(xmlNode *tag) {
  node *tmpNode{nullptr};

  tmpNode = new node;
  tmpNode->ltoken = tagsToken::generateFNVTOKEN((const char *)tag->name);
  switch (tmpNode->ltoken) {
  case tagsToken::token::View:
    resolveProp(tag, viewProp, tmpNode->ltoken);
    break;
  case tagsToken::token::SText:
    resolveProp(tag, TextProp, tmpNode->ltoken);
    break;
  case tagsToken::token::DText:
    resolveProp(tag, TextProp, tmpNode->ltoken);
    break;
  case tagsToken::token::TextInput:

    break;
  }

  return tmpNode;
}

void VALIDATOR::TOKEN::resolveProp(xmlNode *nodeRef, const char *ref[],
                                   uint64_t &type) {
  xmlChar *tmp = nullptr;
  uint64_t token{0};

  while (*ref) {
    tmp = xmlGetProp(nodeRef, (const xmlChar *)*ref);
    if (tmp != NULL) {
      token = tagsToken::generateFNVTOKEN(*ref);
      switch (type) {
      case tagsToken::token::View:
        switch (token) {
        case tagsToken::VIEW_PROP::id:

          break;
        case tagsToken::VIEW_PROP::BgColor:

          break;
        case tagsToken::VIEW_PROP::Margin:

          break;
        case tagsToken::VIEW_PROP::Padding:

          break;
        case tagsToken::VIEW_PROP::Touch:

          break;
        case tagsToken::VIEW_PROP::flex:

          break;
        case tagsToken::VIEW_PROP::flextype:

          break;
        case tagsToken::VIEW_PROP::alignItems:

          break;
        case tagsToken::VIEW_PROP::justifyContent:

          break;
        case tagsToken::VIEW_PROP::warp:

          break;
        case tagsToken::VIEW_PROP::BorderCode:

          break;
        }
        break;
      case tagsToken::token::DText:
        switch (token) {
        case tagsToken::TEXT_PROP::id:
          break;
        }

      case tagsToken::token::SText:
        switch (token) {
        case tagsToken::TEXT_PROP::Color:

          break;
        case tagsToken::TEXT_PROP::Bold:

          break;
        case tagsToken::TEXT_PROP::UnderLine:

          break;
        case tagsToken::TEXT_PROP::Dim:

          break;
        case tagsToken::TEXT_PROP::Blink:

          break;
        case tagsToken::TEXT_PROP::Inverted:

          break;
        case tagsToken::TEXT_PROP::id:

          break;
        }
        break;
      }

      xmlFree(tmp);
    }
    ++ref;
  }
  return;
}

bool VALIDATOR::TOKEN::validateRoot(xmlNode *check) {
  if (xmlStrcmp((const xmlChar *)rootTag, check->name) == 0) {
    return true;
  }
  return false;
}
uint64_t tagsToken::generateFNVTOKEN(const char *delta) {

  uint64_t outMask = 0x00;
  uint32_t offsetMask = 0x811c9dc5;
  uint32_t maskPrime = 0x01000193;

  while (*delta) {
    offsetMask = offsetMask ^ static_cast<uint32_t>(*delta);
    offsetMask = offsetMask * maskPrime;
    ++delta;
  }
  outMask = outMask ^ offsetMask;
  return outMask;
};
