#include "libxml/xmlmemory.h"
#include "libxml/xmlstring.h"
#include <NavigationManager.hpp>
#include <cstring>
#include <iostream>

Screen::Screen(const xmlChar *nav) {

  ScreenName = xmlStrdup(nav);
  return;
}

void Screen::init(int width, int height) {

  ScreenStyle = new __SCREENPROP;
  if (ScreenStyle == nullptr)
    return;
  ScreenStyle->windowWidth = width;
  ScreenStyle->windowHeight = height;

  return;
};

Screen::~Screen() {

  if (ScreenStyle != nullptr)
    delete ScreenStyle;
  if (screenNext != nullptr)
    delete screenNext;
  if (ViewData != nullptr)
    delete ViewData;

  xmlFree(ScreenName);
  return;
}

Node::~Node() {

  if (nodeStyle != nullptr)
    delete nodeStyle;

  if (nodeChild != nullptr)
    delete nodeChild;

  if (nodeNext != nullptr)
    delete nodeNext;

  if (nodeName != nullptr) {
    std::cout << "node exiting " << nodeName << std::endl;
    xmlFree(nodeName);
  }

  return;
}
