#include "TUIE.hpp"
#include "TUIEParser.hpp"
#include "funchelper.hpp"
#include <asm-generic/ioctls.h>
#include <asm-generic/termios.h>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
cursesUI::cursesUI(const char *nameOfFile) {

  int height{0};
  int width{0};
  struct winsize windowParameters;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowParameters);
  height = windowParameters.ws_row;
  width = windowParameters.ws_col;

  XMLParser parserInstance(nameOfFile);
  if (parserInstance.parserStatus()) {
    std::cout << "exiting Parser error code caller"
              << parserInstance.parserStatus() << std::endl;
    return;
  }
  layoutCalculator(parserInstance.getScreenTree()->ViewData, height, width);
  delete parserInstance.getScreenTree();

  return;
};

cursesUI::~cursesUI() {
  // disableRawMode()
  // enableRawMode();
};

void cursesUI::enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    exitSafe(1);
  }

  struct termios raw = orig_termios; // Start with the current settings
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    exitSafe(1);
  }
}

void cursesUI::disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
    exit(1);
  }
}

void cursesUI::doUpdate(int val) {}

void cursesUI::exitSafe(int code) {
  disableRawMode();
  exit(code);
}
