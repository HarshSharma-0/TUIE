#include "Tokens.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <iostream>

node *VALIDATOR::TOKEN::getNextNode(xmlNode *tag) {
  node *tmpNode{nullptr};
  for (const char *token : xmlTags) {
    if (xmlStrcmp((const xmlChar *)token, tag->name) == 0) {
      tmpNode = new node;
      if (tmpNode == nullptr) {
        return nullptr;
      }
      tmpNode->ltoken = tagsToken::tags::VIEW_TOKEN;
    }
  }
  return tmpNode;
}
bool VALIDATOR::TOKEN::validateRoot(xmlNode *check) {
  if (xmlStrcmp((const xmlChar *)rootTag, check->name) == 0) {
    return true;
  }
  return false;
}
