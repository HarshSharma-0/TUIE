#ifndef ENGINE_RENDERER__
#define ENGINE_RENDERER__

// start code = "\033[48;2;"
// foreground color = 255;170;182
// reset ="m"
// start code = "\033[38;2;
// backgrond code = 174;47;0
// reset code = "m"
// wechar = "HELLO!
// reset = "\033[0m"

#include "NavigationManager.hpp"
#include <cstddef>

typedef struct __attribute__((packed)) {
  char startb[10];

  char backr[3];
  char backde[1];
  char backg[3];
  char backd[1];
  char backb[3];
  char resetb[1];

  char startf[10];
  char forer[3];
  char forede[1];
  char foreg[3];
  char fored[1];
  char foreb[3];

  char data[1];
  char reset[7];

  char nullorN[1];
} pixel;

class TUIEEngine {

public:
  TUIEEngine(int &_height, int &_width, Node *_window);
  ~TUIEEngine();

  void drawFromNode(Node *);
  void draw();
  void refresh();
  bool terminate{false};

private:
  pixel *rendererPixel{nullptr};
  size_t sizPixel{0};
  Node *window{nullptr};
  int cells{0};
  int rheight{0};
  int rwidth{0};
};

#endif
