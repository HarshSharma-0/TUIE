#include "init.hpp"
#include "Tokens.hpp"
#include "constantsVT00.hpp"
#include "options.hpp"
#include <asm-generic/ioctls.h>
#include <asm-generic/termbits-common.h>
#include <asm-generic/termbits.h>
#include <asm-generic/termios.h>
#include <bits/ioctl.h>
#include <bits/termios_inlines.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <unistd.h>

INIT_TUIE::INIT_TUIE(char *appName) {
  const char *home = std::getenv("HOME");
  if (home == nullptr) {
    std::cout << "Ensure the home env path exist" << std::endl;
  }
  appPath = home;
  appPath /= __APP_ROOT;
  appPath /= appName;
  if (std::filesystem::exists(appPath) == false) {
    appPath.remove_filename();
    INIT_TUIE::INIT_RAW_MODE();
    if (listAndSelect(appPath) == -1) {
      INIT_TUIE::EXIT_RAW_MODE();
      std::cout << "NOTING SELECTED EXITING" << std::endl;
      std::exit(EXIT_SUCCESS);
    }
    // INIT_TUIE::EXIT_RAW_MODE();
  }
}

int INIT_TUIE::INIT_RAW_MODE() {

  winsize ws;
  if (tcgetattr(STDIN_FILENO, &org_setting) == -1)
    return -1;
  struct termios raw = org_setting;
  raw.c_iflag &= ~(ICRNL | BRKINT | INPCK | IXON | ISTRIP);
  raw.c_oflag &= ~OPOST;
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_cflag |= CS8;
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    return -1;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    return -1;

  INIT_TUIE::windowWidth = ws.ws_col;
  INIT_TUIE::windowHeight = ws.ws_row;

  return 0;
}

int INIT_TUIE::EXIT_RAW_MODE() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &org_setting) == -1)
    return -1;
  return 0;
}
