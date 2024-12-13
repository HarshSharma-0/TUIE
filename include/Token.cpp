#include "Tokens.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

node *VALIDATOR::TOKEN::getNextNode(xmlNode *tag) {
  node *tmpNode{nullptr};

  tmpNode = new node;
  tmpNode->ltoken = tagsToken::generateFNVTOKEN((const char *)tag->name);
  switch (tmpNode->ltoken) {
  case tagsToken::token::View:
    tmpNode->flagView = new configView;
    if (tmpNode->flagView == nullptr) {
      return nullptr;
    }
    resolveProp(tag, viewProp, tmpNode);
    break;
  case tagsToken::token::Text:
    tmpNode->flagText = new Text;
    if (tmpNode->flagText == nullptr) {
      return nullptr;
    }

    resolveProp(tag, TextProp, tmpNode);
    break;
  case tagsToken::token::TextInput:

    break;
  }

  return tmpNode;
}

void VALIDATOR::TOKEN::resolveProp(xmlNode *nodeRef, const char *ref[],
                                   node *type) {
  xmlChar *tmp = nullptr;
  uint64_t token{0};
  std::string color = "/";

  while (*ref) {
    tmp = xmlGetProp(nodeRef, (const xmlChar *)*ref);
    if (tmp != NULL) {
      token = tagsToken::generateFNVTOKEN(*ref);
      switch (type->ltoken) {
      case tagsToken::token::View:
        resolveViewValue(type, token, tmp);
        break;
      case tagsToken::token::Text:
        switch (token) {
        case tagsToken::TEXT_PROP::id:
          type->id = (char *)xmlStrdup(tmp);
          break;
        }
        break;
      }
      xmlFree(tmp);
    }
    ++ref;
  }
  if (color != "/") {
    color += "m";
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
