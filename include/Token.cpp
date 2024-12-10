#include "Tokens.hpp"
#include "libxml/parser.h"
#include "libxml/xmlmemory.h"
#include "libxml/xmlstring.h"
#include <cmath>
#include <cstdint>
#include <iostream>

node *VALIDATOR::TOKEN::getNextNode(xmlNode *tag) {
  node *tmpNode{nullptr};

  tmpNode = new node;
  tmpNode->ltoken = tagsToken::generateFNVTOKEN((const char *)tag->name);
  switch (tmpNode->ltoken) {
  case tagsToken::token::View:
    tagsToken::resolver::resolveView(tagsToken::token::vProp, tag);
    break;
  case tagsToken::token::DText:
    tagsToken::resolver::resolveDText(tagsToken::token::tProp, tag);
    break;
  case tagsToken::token::SText:
    tagsToken::resolver::resolveSText(tagsToken::token::tProp, tag);
    break;
  default:

    break;
  }
  return tmpNode;
}

void tagsToken::resolver::resolveView(const char *ref[], xmlNode *nodeRef) {
  xmlChar *tmp = nullptr;
  uint64_t token{0};

  while (*ref) {
    tmp = xmlGetProp(nodeRef, (const xmlChar *)*ref);
    if (tmp != NULL) {
      token = tagsToken::generateFNVTOKEN(*ref);
      switch (token) {
      case tagsToken::VIEW_PROP::id:
        std::cout << "encountered id" << std::endl;
        break;
      default:
        std::cout << " " << token << " : " << tagsToken::VIEW_PROP::id;
        break;
      }
      xmlFree(tmp);
    }
    ++ref;
  }
  return;
}

void tagsToken::resolver::resolveDText(const char *tRef[], xmlNode *nodeRef) {
  return;
}
void tagsToken::resolver::resolveSText(const char *dRef[], xmlNode *nodeRef) {
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

const char *tagsToken::token::vProp[] = {
    "BgColor", "Border", "Padding", "Margin", "Touch", "id", nullptr};
const char *tagsToken::token::tProp[] = {
    "Color", "Bold", "UnderLine", "Dim", "Blink", "Inverted", "id", nullptr};
