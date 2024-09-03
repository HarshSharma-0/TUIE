#ifndef TUIE_PARSER_H
#define TUIE_PARSER_H

#include <NavigationManager.hpp>
#include <asm-generic/termios.h>
#include <cstdlib>
#include <defs.hpp>
#include <filesystem>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <nodeProperty.hpp>

class XMLParser {
public:
  XMLParser(const char *);
  ~XMLParser();
  bool parserStatus() { return status; };
  Screen *getScreenTree() { return screenTree; }

private:
  std::map<std::string, std::string> fileMap; // <fileName,filepath>
  std::map<std::string, xmlDoc *> moduleMap;
  std::map<std::string, Screen *> modeluStart;

  std::filesystem::path __parsePath = "./";

  bool status{false};
  Screen *screenTree{nullptr};

  void filesystemTree();
  Screen *createScreenTree(xmlNode *);
  Node *createNodeChildrenTree(xmlNode *);
  bool resolveAttr(xmlNode *, const xmlChar *[], const xmlChar *[], Node *);
};

#endif
