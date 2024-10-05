#ifndef NAVIAGTION_MANAGER_HPP
#define NAVIAGTION_MANAGER_HPP

#include <nodeProperty.hpp>

class Node {
public:
  ~Node();
  Node *nodeNext{nullptr};
  Node *nodeChild{nullptr};
  Node *nodePrev{nullptr};
  unsigned char *nodeName{nullptr};
  bool isModule{false};
  int nodeType{0};
  __NODEPROP *nodeStyle{nullptr};
};

class Screen {
public:
  Screen(const unsigned char *);
  ~Screen();
  Screen *screenNext{nullptr};
  Screen *screenPrev{nullptr};
  Node *ViewData{nullptr};
  unsigned char *ScreenName{nullptr};
  __SCREENPROP *ScreenStyle{nullptr};
  void init(int, int);
};

class Navigation {
public:
  Screen *navigator;
  char *navName;

  Navigation(Screen *mainNav) : navigator(mainNav), navName(nullptr) {}

  void Clampnavigator(Screen *tmp) {
    navigator = tmp;
    return;
  }
  void setDimensions(int &deltah, int &deltaw) {
    windowHeight = deltah;
    windowWidth = deltaw;
    return;
  }
  ~Navigation() {
    if (navigator != nullptr)
      delete navigator;
    if (navName != nullptr)
      delete navName;
  }

private:
  int windowHeight{0};
  int windowWidth{0};
};

#endif
