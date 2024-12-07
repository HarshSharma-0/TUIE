#include "parser.hpp"
#include "Tokens.hpp"
#include "libxml/parser.h"
#include "libxml/xmlversion.h"
#include <filesystem>
#include <iostream>

int OPEN_APP::parser(std::filesystem::path &appxml) {
  LIBXML_TEST_VERSION;
  VALIDATOR::TOKEN TOKEN;
  appxml /= __APP_ENTRY;
  if (std::filesystem::exists(appxml) == false) {
    return -1;
  }
  xmlDoc *rootXml{nullptr};
  xmlNode *rootNode{nullptr};
  rootXml = xmlReadFile(appxml.c_str(), NULL, 0);
  if (rootXml == nullptr) {
    return -1;
  }
  rootNode = xmlDocGetRootElement(rootXml);
  for (xmlNode *curNode = rootNode; curNode; curNode = curNode->next) {
    if (curNode->type == XML_ELEMENT_NODE) {
      if (TOKEN.validateRoot(curNode) == true) {
        for (xmlNode *appNode = curNode->children; appNode;
             appNode = appNode->next) {
          if (appNode->type == XML_ELEMENT_NODE) {
          }
        }
      } else {
        return -1;
      }
    }
  }
  return 1;
}
