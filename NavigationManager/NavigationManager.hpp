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
  Screen *View;
  char *navName;

  Navigation(Screen *mainNav) : View(mainNav), navName(nullptr) {}

  ~Navigation() {
    if (View != nullptr)
      delete View;
    if (navName != nullptr)
      delete navName;
  }
};

#endif
