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

void listAndSelect(std::filesystem::path &dir) {
  int selected{0};
  size_t code{0};
  char ch = 'a';
  std::vector<std::filesystem::path> list;

  for (auto const &entry : std::filesystem::directory_iterator(dir)) {
    list.push_back(entry.path());
  }
  CLEARSCREEN;
  CURSORRESET;
  TEXTCOLOR(CYANLF, DEFAULTCOLORB);
  std::cout << "*********************************************";
  BOLDTEXT;
  TEXTCOLOR(GREENF, DEFAULTCOLORB);
  std::cout << " SELECT APP TO OPEN ";
  TEXTCOLOR(CYANLF, DEFAULTCOLORB);
  std::cout << "**********************************************" << std::endl;
  RESETTEXT;
  while (ch != 'q') {
    code = read(STDIN_FILENO, &ch, 1);
    std::cout << ch;
    std::cout.flush();
  }

  std::cout << "exit" << std::endl;
  return;
}
