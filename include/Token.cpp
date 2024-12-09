#include "Tokens.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <cstdint>
#include <iostream>

node *VALIDATOR::TOKEN::getNextNode(xmlNode *tag) {
  node *tmpNode{nullptr};

  tmpNode = new node;
  tmpNode->ltoken = tagsToken::generateFNVTOKEN((const char *)tag->name);

  return tmpNode;
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
  int i = 0;
  while (*delta) {
    offsetMask = offsetMask ^ static_cast<uint32_t>(delta[i]);
    offsetMask = offsetMask * maskPrime;
    ++delta;
  }
  outMask = outMask ^ offsetMask;
  return outMask;
};

uint64_t tagsToken::token::VIEW = tagsToken::generateFNVTOKEN("VIEW");
