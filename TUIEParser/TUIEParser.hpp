#ifndef TUIE_PARSER_H
#define TUIE_PARSER_H

#include "libxml/xmlstring.h"
#include <NavigationManager.hpp>
#include <asm-generic/termios.h>
#include <cstdlib>
#include <defs.hpp>
#include <filesystem>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <nodeProperty.hpp>
#include <string>

class XMLParser {
public:
  XMLParser(const char *);
  ~XMLParser();
  bool parserStatus() { return status; };
  Screen *getScreenTree() { return screenTree; }

private:
  std::map<std::string, std::string> filePathMap; // <fileName,filepath>
  std::map<std::string, xmlDoc *> moduleMapNode;
  std::map<std::string, xmlNode *> extractedModule;
  std::filesystem::path __parsePath = "./";

  bool status{false};
  Screen *screenTree{nullptr};

  void filesystemTree();
  xmlNode *parseModule(const char *);
  Screen *createScreenTree(const char *);
  Node *createNodeChildrenTree(xmlNode *, const char *);
  xmlNode *resolveModule(const char *, const char *);
  bool resolveAttr(xmlNode *, const xmlChar *[], const xmlChar *[], Node *);
};

#endif
