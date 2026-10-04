#include "conio_posix.h"
#include <stdio.h>

void clrscr() {
   printf("\033[2J\033[H");
}

void clreol() {
}

void gotoxy(int x, int y) {
   printf("\033[%d;%dH", y, x); // y goes first and then x.
   fflush(stdout);
}

// Original conio got a method to make colors.
// textbackground(int color); and textcolor(int color);
