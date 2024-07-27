#include "libxml/xmlmemory.h"
#include "libxml/xmlstring.h"
#include <NavigationManager.hpp>
#include <cstring>

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
  ScreenStyle->_windowBuffer = new wchar_t **[2];
  if (ScreenStyle->_windowBuffer == nullptr)
    return;
  for (int i = 0; i < 1; i++) {
    ScreenStyle->_windowBuffer[i] = new wchar_t *[height];
    if (ScreenStyle->_windowBuffer[i])
      return;
    for (int j = 0; j < height; j++) {
      ScreenStyle->_windowBuffer[i][j] = new wchar_t[width];
      if (ScreenStyle->_windowBuffer[i][j] == nullptr)
        return;
    }
  }
  return;
};

Screen::~Screen() {
  if (ScreenStyle != nullptr) {
    for (int i = 0; i < 1; i++) {
      for (int j = 0; j < ScreenStyle->windowHeight; j++) {
        delete[] ScreenStyle->_windowBuffer[i][j];
      }
      delete[] ScreenStyle->_windowBuffer[i];
    }
    delete[] ScreenStyle->_windowBuffer;
  }
  if (screenNext != nullptr) {
    delete screenNext;
  }
  xmlFree(ScreenName);
  return;
}

Node::~Node() {

  if (nodeStyle != nullptr) {
    delete nodeStyle;
  };
  if (nodeChild != nullptr) {
    delete nodeChild;
  }
  if (nodeNext != nullptr) {
    delete nodeNext;
  }
  xmlFree(nodeName);
  return;
}
