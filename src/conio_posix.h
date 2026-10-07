#ifndef _CONIO_POSIX_H_
#define _CONIO_POSIX_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

enum COLORS {
   BLACK,
   BLUE,
   GREEN,
   RED,
   MAGENTA,
   BROWN,
   LIGHTGRAY,
   DARKGRAY,
   LIGHTBLUE,
   LIGHTGREEN,
   LIGHTCYAN,
   LIGHTMAGENTA,
   YELLOW,
   WHITE
}; // How we can do this for POSIX, Like actually.

#define BLINK 128

// Before rebuilding the header. We need to check what is deprecated and what could be useful
// for educational purpose.

// Clear lines and screen functions:

// Full screen cleaning
void clrscr();
void clreol();

void gotoxy(int x, int y);

void textcolor(int color);
void textbackground(int color);

void textattr(int attr);

#ifdef __cplusplus
}
#endif

#endif // _CONIO_POSIX_C_
