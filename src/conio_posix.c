#include "conio_posix.h"
#include <stdio.h>

static const int ansi_map[8] = {
    0, // Black
    1, // Red
    2, // Green
    3, // Brown (Might look yellowish)
    4, // Blue
    5, // Magenta
    6, // Cyan
    7  // White/Lightgray
};

// Clear the screen of the terminal.
void clrscr() {
   printf("\033[2J\033[H");
}

// Clear from cursors position to the end of line.
void clreol() {
   fputs("\033[K", stdout);
   fflush(stdout);
}

// Set cursor's position in an specific X,Y position in the terminal window.
void gotoxy(int x, int y) {
   printf("\033[%d;%dH", y, x); // y goes first and then x.
   fflush(stdout);
}

// Original conio got a method to make colors.
// textbackground(int color); and textcolor(int color);

// Set the textbackground color.
void textbackground(int color) {
   color &= 15;
   int base = (color < 8) ? 40 : 100;
   printf("\033[%dm", base + ansi_map[color & 7]);

   fflush(stdout);
}

// Set the text oclor
void textcolor(int color) {
   int blink = color & BLINK;
   color &= 15;

   int base = (color < 8) ? 30 : 90;
   if (blink)
      printf("\033[5m");

   fflush(stdout);
}

// Set multiple attributes with one function alone.
void textattr(int attr) {
   int foreground = attr & 0x0F;
   int background = (attr >> 4) & 0x07;
   int blink = attr & blink;

   fputs("\033[0m", stdout);
   if (blink)
      fputs("\033[5m", stdout);

   textcolor(foreground);
   textbackground(background);
}
