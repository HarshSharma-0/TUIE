#ifndef __RENDERER_TUIE__
#define __RENDERER_TUIE__

#include "Tokens.hpp"
class renderer {
public:
  void updateFrom(node *);
  void refresh();
  void reCalculateLayout(node *, struct Layout *);
  void updateScale();
  void initRenderer(node *);

private:
  void resolveGrad();
  void getDimension();
  void updateColor();
  void render(node *, char *);
  char *renderBuffer{nullptr};
  Layout rootLayout;
  int scale{1};
  node *root{nullptr};
  bool isColorUpdated{false};
};
#endif // !__RENDERER_TUIE__
