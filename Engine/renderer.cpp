#include "renderer.hpp"
#include "Tokens.hpp"
#include "constantsVT00.hpp"
#include <asm-generic/ioctls.h>
#include <asm-generic/termios.h>
#include <bits/ioctl.h>
#include <cstring>
#include <unistd.h>

void renderer::render(node *__node, char *__tmp) {
  for (int i = 0; i < rootLayout.width * rootLayout.height; i++) {
    renderBuffer[i] = 'a';
  }
  return;
}
void renderer::refresh() {
  CLEARSCREEN;
  CURSORRESET;
  CURSORXY(0, 0);
  for (int i = 0; i < rootLayout.height; i++) {
    write(STDOUT_FILENO, (char *)'1', 1);
    CURSORDOWN(i + 1);
  }

  sleep(5);
  return;
}

void renderer::initRenderer(node *__set) {
  root = __set;
  getDimension();
  renderBuffer = new char[rootLayout.height * rootLayout.width];
  reCalculateLayout(__set, &rootLayout);
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
  rootLayout.offsetX = 0;
  rootLayout.offsetY = 0;

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
  char test[2] = {'U', 'D'};
  int i = 0;
  for (node *cur = __tmpNode; cur; cur = cur->next) {
    switch (cur->ltoken) {
    case tagsToken::token::View:
      cur->layout->height = layout->height * (cur->flagView->flex / totalflex);
      cur->layout->offsetY = clampY;
      clampY += cur->layout->height;
      render(cur, &test[i]);
      i++;
      break;
    }
  }
}