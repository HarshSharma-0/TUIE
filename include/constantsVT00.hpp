#ifndef __VT100_CONSTANTS__
#define __VT100_CONSTANTS__

#include <stdio.h>

// cursor macro
#define ESC "\033"
#define CURSORUP(n) printf(ESC "[%dA", (n))
#define CURSORDOWN(n) printf(ESC "[%dB", (n))
#define CURSORRIGHT(n) printf(ESC "[%dC", (n))
#define CURSORLEFT(n) printf(ESC "[%dD", (n))
#define CURSORXY(X, Y) printf(ESC "[%d;%dH", (X), (Y))
#define CURSORRESET printf(ESC "[f")
#define SCROLLDOWN printf(ESC "D")
#define SCROLLUP printf(ESC "M")

#define SMOOTHSCROLL printf(ESC "[?4h")

// text attribute macro
#define RESETTEXT printf(ESC "[0m")
#define BOLDTEXT printf(ESC "[1m")
#define RESETBOLD printf(ESC "[21m")
#define UNDERLINETEXT printf(ESC "[4m")
#define RESETUNDERLINE printf(ESC "[24m")
#define DIMTEXT printf(ESC "[2m")
#define RESETDIM printf(ESC "[22m")
#define BLINKTEXT printf(ESC "[5m")
#define RESETBLINK printf(ESc "[25m")
#define INVERTEDTEXT printf(ESC "[7m")
#define RESETINVERTED printf(ESC "[27m")
#define INVISIBLETEXT printf(ESC "[8m")
#define RESETINVISIBLE printf(ESC "[28m")

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
// response \033[?1;< terminal code >0c

#endif // !__VT100_CONSTANTS__
