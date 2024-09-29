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
#include <ostream>

/**
 * This is the explanation to the executioin flow of the XMLParser constructor
 * first we extract the HOME enviroment variable and then we check what the
 *function returned
 *
 * if return value is not a nulllptr we proceed further and create the parsing
 *path object and is goes like
 * __parssePath = $HOME/.local/appname and if this path exist we create the
 *filesystem tree with respective file name as key and map that into an std::map
 * and after that we create the screen tree using parser tree
 *
 * if the return value is nullptr the we simply exit the program and continue
 *our termination
 **/

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
    std::cout << "cannot find (.local) folder using your env $HOME"
              << std::endl;
  }
};

/**
 * The desctructor cleans the parser and the doc tree created in parse module
 **/

XMLParser::~XMLParser() {
  for (const auto &[key, value] : moduleMapNode)
    xmlFreeDoc(value);
  xmlCleanupParser();
};

/**
 * Function filesystem tree created the map if the file only with the .xml
 *exxtension and ignore the rest
 **/

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

/**
 * Functoin parseModule is used to create the map of the xml parsed data so
 * whenever we require a specific module we can probe the map if the module
 * exist we return the xmlNode else if the module is not parsed it is parsed and
 * returned but first we check if the module exist or not so reduce the compute
 * cost
 **/

xmlNode *XMLParser::parseModule(const char *modulefilename) {

  if (filePathMap.find(modulefilename) != filePathMap.end()) {
    if (moduleMapNode.find(modulefilename) != moduleMapNode.end()) {
      return xmlDocGetRootElement(moduleMapNode[modulefilename]);
    }
    // part below runs if the module doesnt exist
    xmlDoc *temp{nullptr};
    temp = xmlReadFile(filePathMap[modulefilename].c_str(), nullptr, 0);
    moduleMapNode[modulefilename] = temp;
    return xmlDocGetRootElement(temp);
  }
  return nullptr;
}

/**
 * Funtion resolveModule is used to extract module from the xml tree and map
 * each xml module node to the expected map and preserve the informatijon for
 * further use if there exist the module in map it is checked first and returned
 * and we also check if the paremeter in the module is correct or not to provide
 * a accurute verbose of the where is the error or in which file
 **/

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
      if (xmlStrEqual(cur_node->name, (const xmlChar *)"ModuleView") == 1) {
        xmlChar *moduleName{nullptr};
        moduleName = xmlGetProp(cur_node, (const xmlChar *)"ModuleName");
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
  return extractedModule[moduleName];
}

/**
 * Function createScreenTree is the function that is called for the root file of
 * the app and the screens are processed and the childrens are extracted and all
 * the relative information that a sceen must have for now there only exist the
 * nav name but in future fruther more tags will be added in the screen tag also
 * in this function we use crawler to crawl over the tree and bind the specific
 * node in tree with correct data
 **/

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
    if (cur_node->type == XML_ELEMENT_NODE) {
      if (xmlStrEqual((const xmlChar *)"Screen", cur_node->name) == 1) {
        if (crawler != nullptr) {
          crawler->screenPrev = crawler;
          crawler->screenNext = new Screen(cur_node->name);
          crawler = crawler->screenNext;
        }
        if (root == nullptr) {
          root = new Screen(cur_node->name);
          crawler = root;
        }
      }

      crawler->ViewData = createNodeChildrenTree(cur_node->children, rootFile);

      if (status) {
        return nullptr;
      }
    }
  }

  return root;
}

/**
 * Function createNodeChildrenTree is used to parse and create the node of the
 * tags other than screen that a specific sceen is expeced to render , it uses
 * simple method to parse specific node and each node have the given a unique id
 * that can be used to identify the node type it also utilises the crawler to
 * crawl over the tree and to add relivent data and node to the tree and a
 * function to extract the props a node have
 *
 * **/

Node *XMLParser::createNodeChildrenTree(xmlNode *child,
                                        const char *currentfile) {

  Node *children{nullptr};
  Node *crawler{nullptr};

  for (xmlNode *cur_node = child; cur_node; cur_node = cur_node->next) {

    if (cur_node->type == XML_ELEMENT_NODE) {
      for (int i = 0; predefinedRenderMap[i] != nullptr; i++) {
        if (xmlStrEqual(cur_node->name, predefinedRenderMap[i]) == 1) {

          if (i == RenderTypes::ENGINE_MODULE_DEFINE) {
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

              Node *temp =
                  createNodeChildrenTree(aux, (const char *)moduleFile);
              if (children == nullptr) {
                children = temp;
                crawler = children;
              } else {
                crawler->nodePrev = crawler;
                crawler->nodeNext = temp;
                crawler = crawler->nodeNext;
              }
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

          if (children == nullptr) {
            children = new Node;
            crawler = children;
          } else {
            crawler->nodePrev = crawler;
            crawler->nodeNext = new Node;
            crawler = crawler->nodeNext;
          }

          crawler->nodeStyle = new __NODEPROP;
          crawler->nodeStyle->flex = 1;
          crawler->nodeStyle->flexDirection = RenderTypes::FLEX_DIRECTION_ROW;
          if (resolveAttr(cur_node, tagProp, predefinedAlignAttributes,
                          crawler) != true) {
            delete children;
            return nullptr;
          }
          crawler->nodeType = i;
          if (cur_node->children) {
            crawler->nodeChild =
                createNodeChildrenTree(cur_node->children, currentfile);
          }
        }
      }
    }
  }
  return children;
}

/**
 * The entire purpose of the resolveAttr function is to extract the props in the
 * xml node and created the copy of that attribute in the node that the renderr
 * can understand and utilise
 * **/

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
      case 9:
        cpy->nodeStyle->flexDirection = xmlChartoi(attrId);
        break;
      case 10:
        cpy->nodeStyle->color = xmlStrdup(attrId);
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
