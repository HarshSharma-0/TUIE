#ifndef __VT100_CONSTANTS__
#define __VT100_CONSTANTS__

#include <stdio.h>

#define ESCSTART "\033["
#define ESCEND "m"
// cursor macro
#define ESCC '\033'
#define ESC "\033"
#define CURSORUP(n) printf(ESC "[%dA", (n))
#define CURSORDOWN(n) printf(ESC "[%dB", (n))
#define CURSORRIGHT(n) printf(ESC "[%dC", (n))
#define CURSORLEFT(n) printf(ESC "[%dD", (n))
#define CURSORXY(Y, X) printf(ESC "[%d;%dH", (Y), (X))
#define CURSORRESET printf(ESC "[H")
#define SCROLLDOWN printf(ESC "D")
#define SCROLLUP printf(ESC "M")
#define CURSORHIDE printf(ESC "[?25l")
#define CURSORSHOW printf(ESC "[?25h")
#define SMOOTHSCROLL printf(ESC "[?4h")

// text attribute macro
#define RESETTEXT printf(ESC "[0m");
#define BOLDTEXT "1"
#define RESETBOLD "21"
#define UNDERLINETEXT "4"
#define RESETUNDERLINE "24"
#define DIMTEXT "2"
#define RESETDIM "22"
#define BLINKTEXT "5"
#define RESETBLINK "25"
#define INVERTEDTEXT "7"
#define RESETINVERTED "27"
#define INVISIBLETEXT "8"
#define RESETINVISIBLE "28"

#define SETWIN(W, H) printf(ESC "[%d;%dr", (W), (H))
#define CLEARRIGHT printf(ESC "[K")
#define CLEARLEFT printf(ESC "[1K")
#define CLEARLINE printf(ESC "[2K")

#define CLEARDOWN printf(ESC "[J")
#define CLEARUP printf(ESC "[1J")
#define CLEARSCREEN printf(ESC "[2J")
#define CLEARSCROLl printf(ESC "[3J")

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
