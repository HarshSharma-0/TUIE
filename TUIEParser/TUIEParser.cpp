#include "NavigationManager.hpp"
#include "funchelper.hpp"
#include "libxml/parser.h"
#include "libxml/xmlerror.h"
#include "libxml/xmlmemory.h"
#include "libxml/xmlstring.h"
#include "nodeProperty.hpp"
#include <TUIEParser.hpp>
#include <cstddef>
#include <cstring>
#include <defs.hpp>
#include <iostream>
#include <ostream>

XMLParser::XMLParser(const char *filename) {

  LIBXML_TEST_VERSION
  const char *env_Prefix = std::getenv("HOME");
  if (env_Prefix != nullptr) {
    __parsePath = env_Prefix;
    __parsePath /= ".local";
    __parsePath /= filename;
    if (std::filesystem::exists(__parsePath)) {
      std::filesystem::current_path(__parsePath);
      status = treeAndReadXmlFile();
    } else {
      std::cout << "please give correct app name" << __parsePath << std::endl;
    }

  } else {
    std::cout << "please set your prefix to the installation dir of the app";
  }
};

XMLParser::~XMLParser() {
  for (const auto &[key, value] : moduleMap)
    xmlFreeDoc(value);
  xmlCleanupParser();
};

bool XMLParser::treeAndReadXmlFile() {
  for (const auto &parserIterator :
       std::filesystem::recursive_directory_iterator(__parsePath)) {
    if (parserIterator.is_regular_file()) {
      if (parserIterator.path().extension() == ".xml") {
        moduleMap[parserIterator.path().filename().string()] =
            xmlReadFile(parserIterator.path().string().c_str(), nullptr, 0);
        if (moduleMap[parserIterator.path().filename().string()] == nullptr) {
          std::cout << "error parsing file" << std::endl;
          return false;
        }
      }
    }
  }

  screenTree = createXmlTree(xmlDocGetRootElement(moduleMap[rootFileName]));

  if (screenTree != nullptr)
    return true;
  return false;
}

Screen *XMLParser::createXmlTree(xmlNode *rootElement) {

  Screen *root{nullptr};
  Screen *crawler{nullptr};
  int **screenDimensionMatrix{nullptr};

  if (xmlStrEqual(rootElement->name, predefinedRootTag) != 1) {
    std::cout << "root element not <cursesEngine> exiting" << std::endl;
    return nullptr;
  }

  for (xmlNode *cur_node = rootElement->children; cur_node;
       cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrEqual((const xmlChar *)"Screen", cur_node->name) == 1) {
        if (crawler != nullptr) {
          crawler->screenNext = new Screen(cur_node->name);
          crawler = crawler->screenNext;
        }
        if (root == nullptr) {
          root = new Screen(cur_node->name);
          crawler = root;
        }
      }

      crawler->ViewData = createXmlChildrenTree(cur_node->children);
    }
  }

  return root;
}

Node *XMLParser::createXmlChildrenTree(xmlNode *child) {

  Node *children{nullptr};
  Node *crawler{nullptr};

  for (xmlNode *cur_node = child; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      for (int i = 0; predefinedRenderMap[i] != nullptr; i++) {
        if (xmlStrEqual(cur_node->name, predefinedRenderMap[i]) == 1) {
          if (children == nullptr) {
            children = new Node;
            crawler = children;
          }
          if (children != nullptr) {
            crawler->nodeNext = new Node;
            crawler = crawler->nodeNext;
          }
          crawler->nodeStyle = new __NODEPROP;

          if (resolveAttr(cur_node, tagProp, predefinedAlignAttributes,
                          crawler) != true) {
            std::cout << "before free" << std::endl;
            delete children;
            std::cout << "after children" << std::endl;
            return nullptr;
          }

          crawler->nodeType = i;
          crawler->nodeChild = createXmlChildrenTree(cur_node->children);
        }
      }
    }
  }

  return children;
}

bool XMLParser::resolveAttr(xmlNode *__node, const xmlChar *__from[],
                            const xmlChar *__to[], Node *cpy) {
  xmlChar *attrId{nullptr};

  for (int i = 0; __from[i] != nullptr; i++) {
    attrId = xmlGetProp(__node, __from[i]);
    if (attrId != NULL) {
      switch (i) {
      case 0:
        cpy->nodeName = xmlStrdup(attrId);
        break;
      case 1:
        cpy->nodeStyle->flex = xmlChartoi(attrId);
        break;
      case 4:
        cpy->nodeStyle->backgroundColor = xmlStrdup(attrId);
        break;
      case 5:
        cpy->nodeStyle->margin = xmlChartoi(attrId);
        break;
      case 6:
        cpy->nodeStyle->padding = xmlChartoi(attrId);
        break;
      case 7:
        break;
      case 8:
        cpy->nodeStyle->bordercolor = xmlStrdup(attrId);
        break;
      default:
        for (int j = 0; __to[j] != nullptr; j++) {
          if (xmlStrEqual(__to[j], attrId) == 1) {
            if (i == 3)
              cpy->nodeStyle->justify = j;
            cpy->nodeStyle->align = j;
          }
        }
        break;
      }

      xmlFree(attrId);
    } else {
      if (i == 0) {
        std::cout << "please check you file name"
                  << "missing id tag always provide id "
                  << "in your components" << std::endl;
        return false;
      }
    }
  }
  return true;
}
