#include "renderer.hpp"
#include "Tokens.hpp"
#include "constantsVT00.hpp"
#include <asm-generic/ioctls.h>
#include <asm-generic/termios.h>
#include <bits/ioctl.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

void renderer::render(node *__node) {
  const char borderh = '-';
  const char borderv = '|';
  int index = 0;
  // Top horizontal border
  for (int i = 0; i < __node->layout->width; i++) {
    index = (__node->layout->offsetY * rootLayout.width) - 1;
    index += __node->layout->offsetX + i;
    renderBuffer[index] = borderh;
  }

  return;
}

void renderer::refresh() {
  CLEARSCROLl;
  CURSORRESET;
  std::cout.flush();
  for (int i = 0; i < rootLayout.height; i++) {
    CURSORXY(i + 1, 1);
    write(STDOUT_FILENO, &renderBuffer[(rootLayout.width * i)],
          rootLayout.width);
  }
  sleep(5);
  return;
}

void renderer::initRenderer(node *__set) {
  root = __set;
  getDimension();
  //  reCalculateLayout(__set, &rootLayout);
  //  updateColor();
  refresh();
  return;
};

void renderer::getDimension() {
  winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
    return;
  }
  rootLayout.height = ws.ws_row;
  rootLayout.width = ws.ws_col;
  rootLayout.cells = ws.ws_col * ws.ws_row;
  renderBuffer = new char[rootLayout.cells];
  for (int i = 0; i < rootLayout.cells; i++) {
    renderBuffer[i] = '0';
  }
  rootLayout.offsetX = 0;
  rootLayout.offsetY = 0;
  SETWIN(1, ws.ws_row);
  return;
}

void renderer::reCalculateLayout(node *__tmpNode, struct Layout *layout) {

  int totalflex{0};
  int clampX = layout->offsetX;
  int clampY = layout->offsetY;

  for (node *cur = __tmpNode; cur; cur = cur->next) {
    cur->layout = new Layout;
    if (cur->layout == nullptr) {
      return;
    }

    switch (cur->ltoken) {
    case tagsToken::token::View:
      totalflex = cur->flagView->flex;
      break;
    case tagsToken::token::Text:
      cur->layout->height = 1;
      //      cur->layout->width = std::strlen(cur->flagText->textBlob);
      cur->layout->offsetX = clampX;
      cur->layout->offsetY = clampY;
      clampY += 1;

      break;
    default:

      break;
    }
  }

  for (node *cur = __tmpNode; cur; cur = cur->next) {

    switch (cur->ltoken) {
    case tagsToken::token::View:
      cur->layout->height = layout->height * (cur->flagView->flex / totalflex);
      cur->layout->offsetY = clampY;
      clampY += cur->layout->height;
      render(cur);
      break;
    }
  }
}
