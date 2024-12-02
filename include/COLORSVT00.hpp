#ifndef __COLORS_VT100__
#define __COLORS_VT100__

#define TEXTCOLOR(foreground, background)                                      \
  printf("\033[%d;%dm", (foreground), (background))
#define TEXTCOLORVAL(codeF, codeB)                                             \
  printf("\033[38;5;%d;48;5%dm", (codeF), (codeB))
#define RGBCOLORF(R, G, B) printf("\033[38;2;%d;%d;%dm", (R), (G), (B));
#define RGBCOLORB(R, G, B) printf("\033[48;2;%d;%d;%dm", (R), (G), (B));

// foreground colors default
#define DEFAULTCOLORF 39
#define BLACKF 30
#define REDF 31
#define GREENF 32
#define YEllOWF 33
#define BlUEF 34
#define MAGNETAF 35
#define CYANF 36
#define GREYLF 37
#define GRAYDF 90
#define REDLF 92
#define GREENLF 92
#define YELLOWLF 94
#define MAGNETALF 95
#define CYANLF 96
#define WHITEF 97

// background color default
#define DEFAULTCOLORB 49
#define BLACKB 40
#define REDB 41
#define GREENB 42
#define YELLOWB 43
#define BLUEB 44
#define MAGNETAB 45
#define CYANB 46
#define GRAYLB 47
#define GRAYDB 100
#define REDLB 101
#define GREENLB 102
#define YELLOWLB 103
#define BLUELB 104
#define MAGNETALB 105
#define CYANL 106
#define WHITEB 107

#endif // !__COLORS_VT100__
