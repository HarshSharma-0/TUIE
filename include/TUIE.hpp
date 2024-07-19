#ifndef TUIE_H
#define TUIE_H

#include <termios.h>

class cursesUI {
public:
  cursesUI(const char *);
  ~cursesUI();

  void doUpdate(int);

private:
  void enableRawMode();
  void disableRawMode();
  void exitSafe(int);
  struct termios orig_termios;
};

#endif // CURSESUI_H
