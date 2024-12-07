#include "Tokens.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"

node *VALIDATOR::TOKEN::getNextNode(xmlNode *tag) {
  node *tmpNode{nullptr};

  return tmpNode;
}
bool VALIDATOR::TOKEN::validateRoot(xmlNode *check) {
  if (xmlStrcmp((const xmlChar *)rootTag, check->name) == 0) {
    return true;
  }
  return false;
}
