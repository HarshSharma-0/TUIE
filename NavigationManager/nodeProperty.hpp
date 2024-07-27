#ifndef NODE_PROP_H
#define NODE_PROP_H

typedef struct StyleProp {
  int offSetX;
  int offSetY;
  int height;
  int width;
  int align;
  int justify;
  int margin;
  int padding;
  int flexDirection;
  int flex;
  unsigned char *backgroundColor;
  unsigned char *bordercolor;
  unsigned char *color;
} __NODEPROP;

typedef struct ScreenProp {
  int windowHeight;
  int windowWidth;
  unsigned char ***_windowBuffer;
  int ***_colorMatrix;
  char *_navName;
} __SCREENPROP;

#endif
