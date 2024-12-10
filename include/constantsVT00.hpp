#ifndef __VT100_CONSTANTS__
#define __VT100_CONSTANTS__

#include <stdio.h>

// cursor macro
#define ESCC '\033'
#define ESC "\033"
#define CURSORUP(n) printf(ESC "[%dA", (n))
#define CURSORDOWN(n) printf(ESC "[%dB", (n))
#define CURSORRIGHT(n) printf(ESC "[%dC", (n))
#define CURSORLEFT(n) printf(ESC "[%dD", (n))
#define CURSORXY(Y, X) printf(ESC "[%d;%dH", (Y), (X))
#define CURSORRESET printf(ESC "[f")
#define SCROLLDOWN printf(ESC "D")
#define SCROLLUP printf(ESC "M")
#define CURSORHIDE printf(ESC "[?25l")
#define CURSORSHOW printf(ESC "[?25h")
#define SMOOTHSCROLL printf(ESC "[?4h")

// text attribute macro
#define RESETTEXT printf(ESC "[0m");
#define BOLDTEXT "\033[1m"
#define RESETBOLD "\033[21m"
#define UNDERLINETEXT "\033[4m"
#define RESETUNDERLINE "\033[24m"
#define DIMTEXT "\033[2m"
#define RESETDIM "\033[22m"
#define BLINKTEXT "\033[5m"
#define RESETBLINK "\033[25m"
#define INVERTEDTEXT "\033[7m"
#define RESETINVERTED "\033[27m"
#define INVISIBLETEXT "\033[8m"
#define RESETINVISIBLE "\033[28m"

#define SETWIN(W, H) printf(ESC "[%d;%dr", (W), (H))
#define CLEARRIGHT printf(ESC "[K")
#define CLEARLEFT printf(ESC "[1K")
#define CLEARLINE printf(ESC "[2K")

#define CLEARDOWN printf(ESC "[J")
#define CLEARUP printf(ESC "[1J")
#define CLEARSCREEN printf(ESC "[2J")

#define DEVSTAT printf(ESC "5n")
#define DEVOK "\0330n"
#define DEVNOK "\0333n"

#define CURSORPOS "\0336n"
// response \033<w>;<h>R

#define GETTERMTYPE printf(ESC "[c")
#define SEQ_START '['
#define KEY_UP 'A'
#define KEY_DOWN 'B'
#define KEY_RIGHT 'C'
#define KEY_LEFT 'D'
// response \033[?1;< terminal code >0c

#endif // !__VT100_CONSTANTS__
