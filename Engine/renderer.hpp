#ifndef __RENDERER_TUIE__
#define __RENDERER_TUIE__

#include "Tokens.hpp"
class renderer {
public:
  void updateFron(node *);
  void refresh();
  void render();
  void reCalculateLayout();
  void updateScale();
  void setNode(node *);

private:
  void resolveGrad();
  void getDimension();
  void updateColor();
  char *renderBuffer{nullptr};
  int *bufferHeight{nullptr};
  int *bufferWidth{nullptr};
  int scale{1};
  node *root{nullptr};
};
#endif // !__RENDERER_TUIE__
