#include "options.hpp"
#include "COLORSVT00.hpp"
#include "constantsVT00.hpp"
#include <asm-generic/termbits-common.h>
#include <bits/termios_inlines.h>
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <vector>

int listAndSelect(std::filesystem::path &dir) {
  CURSORHIDE;
  int selected{0};
  char ch = 'a';
  char seq[2];
  std::size_t length = {0};
  std::vector<std::filesystem::path> list;

  for (auto const &entry : std::filesystem::directory_iterator(dir)) {
    list.push_back(entry.path());
  }
  length = list.size();
  CLEARSCREEN;
  CURSORRESET;
  TEXTCOLOR(CYANLF, DEFAULTCOLORB);
  std::cout << "*********************************************" << BOLDTEXT;
  TEXTCOLOR(GREENF, DEFAULTCOLORB);
  std::cout << " SELECT APP TO OPEN ";
  TEXTCOLOR(CYANLF, DEFAULTCOLORB);
  std::cout << "**********************************************" << std::endl;
  RESETTEXT;

  while (ch != '\r') {
    if (ch == 'q') {
      CURSORRESET;
      CLEARSCREEN;
      CURSORSHOW;
      return -1;
    }
    for (int i = 0; i < length; i++) {

      CURSORXY(i + 2, 1);
      if (i == selected) {
        TEXTCOLOR(REDLF, DEFAULTCOLORB);
        std::cout << ESCSTART << BOLDTEXT << UNDERLINETEXT << ESCEND << list[i];
        RESETTEXT;
      } else {
        std::cout << list[i] << "\n";
      }
      std::cout.flush();
    }
    if (read(STDIN_FILENO, &ch, 1) != 1)
      ch = 'q';
    switch (ch) {
    case ESCC:
      if (read(STDIN_FILENO, &seq[0], 1) != 1)
        ch = 'q';
      if (seq[0] == SEQ_START) {
        if (read(STDIN_FILENO, &seq[1], 1) != 1)
          ch = 'q';
        switch (seq[1]) {
        case KEY_UP:
          if (selected != 0) {
            selected--;
          } else {
            selected = (length - 1);
          }
          break;
        case KEY_DOWN:
          if (selected != (length - 1)) {
            selected++;
          } else {
            selected = 0;
          }

          break;
        default:

          break;
        }
      }
      break;
    default:
      break;
    }
    std::cout.flush();
  }
  CURSORRESET;
  CLEARSCREEN;
  CURSORSHOW;
  dir = list[selected];
  return 0;
}
