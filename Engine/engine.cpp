#include "NavigationManager.hpp"
#include <engine.hpp>
#include <unistd.h>

TUIEEngine::TUIEEngine(int &_height, int &_width, Node *_window) {
  rheight = _height;
  rwidth = _width;
  cells = _height * _width;
  sizPixel = cells * sizeof(pixel);
  rendererPixel = new pixel[cells];
  if (rendererPixel == nullptr) {
    terminate = true;
    return;
  }
  window = _window;
  for (int i = 0; i < cells; i++) {
  }
}

TUIEEngine::~TUIEEngine() {
  if (rendererPixel != nullptr) {
    delete rendererPixel;
  }
}

void TUIEEngine::drawFromNode(Node *_startNode) { return; }

void TUIEEngine::draw() { return; }

void TUIEEngine::refresh() { write(STDOUT_FILENO, rendererPixel, sizPixel); }
