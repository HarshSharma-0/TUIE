#ifndef TUIE_H
#define TUIE_H

#include "NavigationManager.hpp"
#include <termios.h>

class TUIE {
public:
  TUIE(const char *);
  ~TUIE() {
    if (TUIEwindow != nullptr)
      delete TUIEwindow;
  }
  void enableRawMode();
  void disableRawMode();
  Screen *TUIEwindow{nullptr};

private:
  void exitSafe(int);
  struct termios orig_termios;
};

#endif
