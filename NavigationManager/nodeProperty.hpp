#ifndef NODE_PROP_H
#define NODE_PROP_H

typedef struct StyleProp {
  int offSetX;                    // offset of node in x-axis
  int offSetY;                    // offset of node in y-axis
  int height;                     // height of node
  int width;                      // width of node
  int align;                      // align property of the node
  int justify;                    // justify property of the node
  int margin;                     // margin usually 1 or 2
  int padding;                    // padding usuallly 1 or 2
  int flexDirection;              // flexdirection row or coloumn
  float flex;                     // flex value of the node
  unsigned char *backgroundColor; // background color of the node
  unsigned char *bordercolor;     // border color of the node
  unsigned char *color;           // ussed for the text node for the text color
} __NODEPROP;

typedef struct ScreenProp {
  int windowHeight; // height of the entire screen in terminal formnat
  int windowWidth;  // width of the entire screen in terminal format
  char *_navName;   // navigation name of the screen
} __SCREENPROP;

#endif
