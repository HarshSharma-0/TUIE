#include "NavigationManager.hpp"
#include "funchelper.hpp"
#include "libxml/parser.h"
#include "libxml/xmlmemory.h"
#include "libxml/xmlstring.h"
#include "nodeProperty.hpp"
#include <TUIEParser.hpp>
#include <cstddef>
#include <cstring>
#include <defs.hpp>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

XMLParser::XMLParser(const char *fileName) {

  LIBXML_TEST_VERSION
  const char *env_Prefix = std::getenv("HOME");
  if (env_Prefix != nullptr) {
    __parsePath = env_Prefix;
    __parsePath /= ".local";
    __parsePath /= fileName;
    if (std::filesystem::exists(__parsePath)) {
      std::filesystem::current_path(__parsePath);
      filesystemTree();
      screenTree = createScreenTree(rootFileName);
    } else {
      std::cout << "please give correct app name" << __parsePath << std::endl;
    }

  } else {
    std::cout << "please set your prefix to the installation dir of the app";
  }
};

XMLParser::~XMLParser() {
  for (const auto &[key, value] : moduleMapNode)
    xmlFreeDoc(value);
  xmlCleanupParser();
};

void XMLParser::filesystemTree() {
  for (const auto &parserIterator :
       std::filesystem::recursive_directory_iterator(__parsePath)) {
    if (parserIterator.is_regular_file()) {
      if (parserIterator.path().extension() == ".xml") {
        filePathMap[parserIterator.path().filename().string()] =
            parserIterator.path().string();
      }
    }
  }
  return;
}

xmlNode *XMLParser::parseModule(const char *modulefilename) {

  if (filePathMap.find(modulefilename) != filePathMap.end()) {
    if (moduleMapNode.find(modulefilename) != moduleMapNode.end()) {
      return xmlDocGetRootElement(moduleMapNode[modulefilename]);
    }

    xmlDoc *temp{nullptr};
    temp = xmlReadFile(filePathMap[modulefilename].c_str(), nullptr, 0);
    moduleMapNode[modulefilename] = temp;
    return xmlDocGetRootElement(temp);
  }
  return nullptr;
}

xmlNode *XMLParser::resolveModule(const char *moduleName,
                                  const char *moduleFile) {

  if (extractedModule.find(moduleName) != extractedModule.end()) {
    return extractedModule[moduleName];
  }

  xmlNode *temp_node{nullptr};
  temp_node = parseModule(moduleFile);
  if (temp_node == nullptr) {
    return nullptr;
  }
  for (xmlNode *cur_node = temp_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrEqual(cur_node->name, (const xmlChar *)"ModuleDefine") == 1) {
        xmlChar *moduleName{nullptr};
        moduleName = xmlGetProp(cur_node, (const xmlChar *)"name");
        if (moduleName == NULL) {
          std::cout << "Module declaration on file not contain module name"
                    << std::endl
                    << "error in module file" << filePathMap[moduleFile]
                    << std::endl;
          xmlFree(moduleName);
          return nullptr;
        }
        extractedModule[(const char *)moduleName] = cur_node->children;
      }
    }
  }
  if (extractedModule.find(moduleName) == extractedModule.end()) {
    std::cout << "module not found exiting caller " << std::endl
              << "error in file" << filePathMap[moduleFile] << std::endl;
    return nullptr;
  }
  std::cout << "returning test module" << std::endl;
  return extractedModule[moduleName];
}

Screen *XMLParser::createScreenTree(const char *rootFile) {

  xmlNode *rootElement = parseModule(rootFile);
  Screen *root{nullptr};
  Screen *crawler{nullptr};

  if (xmlStrEqual(rootElement->name, predefinedRootTag) != 1) {
    std::cout << "root element not <cursesEngine> exiting" << std::endl;
    return nullptr;
  }

  for (xmlNode *cur_node = rootElement->children; cur_node;
       cur_node = cur_node->next) {
    std::cout << cur_node->name << std::endl;
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

      crawler->ViewData = createNodeChildrenTree(cur_node->children, rootFile);
      if (crawler->ViewData == nullptr) {
        status = true;
        return nullptr;
      }
    }
  }

  return root;
}

Node *XMLParser::createNodeChildrenTree(xmlNode *child,
                                        const char *currentfile) {

  Node *children{nullptr};
  Node *crawler{nullptr};
  std::cout << "called for file " << filePathMap[currentfile] << std::endl;

  for (xmlNode *cur_node = child; cur_node; cur_node = cur_node->next) {
    std::cout << "in loop in file " << filePathMap[currentfile] << std::endl;
    if (cur_node->type == XML_ELEMENT_NODE) {
      for (int i = 0; predefinedRenderMap[i] != nullptr; i++) {
        if (xmlStrEqual(cur_node->name, predefinedRenderMap[i]) == 1) {
          std::cout << "node type " << predefinedRenderMap[i] << std::endl;
          if (children == nullptr) {
            children = new Node;
            crawler = children;
          }

          if (i == RenderTypes::ENGINE_MODULE) {
            xmlChar *moduleFile{nullptr};
            moduleFile = xmlGetProp(cur_node, (const xmlChar *)"fileName");
            if (moduleFile != NULL) {
              xmlChar *moduleID{nullptr};
              xmlChar *moduleName{nullptr};
              moduleID = xmlGetProp(cur_node, (const xmlChar *)"moduleId");

              if (moduleID == NULL) {
                std::cout << "module id not found while trying to parse file:"
                          << std::endl
                          << "error in file" << filePathMap[currentfile]
                          << std::endl;
                xmlFree(moduleID);
                return nullptr;
              }
              moduleName = xmlGetProp(cur_node, (const xmlChar *)"moduleName");
              if (moduleName == NULL) {
                std::cout << "please provide module name :" << std::endl
                          << "error in file" << filePathMap[currentfile]
                          << std::endl;
                xmlFree(moduleName);
                return nullptr;
              }
              xmlNode *aux = resolveModule((const char *)moduleName,
                                           (const char *)moduleFile);
              crawler->nodeChild =
                  createNodeChildrenTree(aux, (const char *)moduleFile);
              xmlFree(moduleName);
              xmlFree(moduleFile);
              xmlFree(moduleID);
              continue;
            }
            std::cout << "module file doesnt exist" << std::endl
                      << "module used in file :" << filePathMap[currentfile]
                      << std::endl;
            xmlFree(moduleFile);
            delete children;
            return nullptr;
          }
          if (children != nullptr) {
            crawler->nodeNext = new Node;
            crawler = crawler->nodeNext;
          }
          crawler->nodeStyle = new __NODEPROP;
          if (resolveAttr(cur_node, tagProp, predefinedAlignAttributes,
                          crawler) != true) {
            delete children;
            return nullptr;
          }
          crawler->nodeType = i;
          if (cur_node->children) {
            crawler->nodeChild =
                createNodeChildrenTree(cur_node->children, currentfile);
            if (crawler->nodeChild == nullptr)
              return nullptr;
          }
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
    }
  }
  return true;
}
