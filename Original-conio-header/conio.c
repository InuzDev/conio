/* A conio implementation for Mingw/Dev-C++.
 *
 * Written by:
 * Hongli Lai <hongli@telekabel.nl>
 * tkorrovi <tkorrovi@altavista.net> on 2002/02/26.
 * Andrew Westcott <ajwestco@users.sourceforge.net>
 *
 * Offered for use in the public domain without any warranty.
 */

// Most variables information used for the arguments in the functions are located in the .h(eader) file.

#ifndef _CONIO_C_
#define _CONIO_C_

#include "conio.h"
#include <string.h>
#include <unistd.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

// Clear the "screen". This actually overwrites every cell with a blank space in the current colors.
// The problem with this function is it limited to 80*25 screens. Terminals nowadays are resizable, this alone make
// this function deprecated to use.
//
// This could be deprecated since we can clear the screen with more native commands nowadays.
void clrscr() {
   DWORD written;

   FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), // The (COORD) says where to start, not where the cursor is located. which also can be specified with {0, 0}, or with a variable
                              __FOREGROUND + (__BACKGROUND << 4), 2000, (COORD){0, 0},
                              &written);
   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
                              2000, (COORD){0, 0}, &written);
   gotoxy(1, 1);
}

// clreol means "Clear to end of line". It blanks from the cursor to the right edge of the current row.
// This could be useful if set correctly in dynamic screens.
//
// This could be used to clear an specific area.
void clreol() {
   COORD coord;
   DWORD written;
   CONSOLE_SCREEN_BUFFER_INFO info;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
                              &info);
   // Here we specify (COOR){x, y}.
   coord.X = info.dwCursorPosition.X;
   coord.Y = info.dwCursorPosition.Y;

   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),
                              ' ', info.dwSize.X - info.dwCursorPosition.X, coord, &written);
   gotoxy(coord.X, coord.Y);
}

// Clear an entire line, delline meaning delete line.
//
// This could be deprecated by the function above.
void delline() {
   COORD coord;
   DWORD written;
   CONSOLE_SCREEN_BUFFER_INFO info;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
                              &info);
   coord.X = info.dwCursorPosition.X;
   coord.Y = info.dwCursorPosition.Y;

   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),
                              ' ', info.dwSize.X * info.dwCursorPosition.Y, coord, &written);
   gotoxy(info.dwCursorPosition.X + 1,
          info.dwCursorPosition.Y + 1);
}

// It will get a text,
int _conio_gettext(int left, int top, int right, int bottom,
                   char *str) {
   int i, j, n;
   SMALL_RECT r;
   CHAR_INFO buffer[25][80];

   r = (SMALL_RECT){left - 1, top - 1, right - 1, bottom - 1};
   ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),
                     (PCHAR_INFO)buffer, (COORD){80, 25}, (COORD){0, 0}, &r);

   lstrcpy(str, "");
   for (i = n = 0; i <= bottom - top; i++)
      for (j = 0; j <= right - left; j++) {
         str[n] = buffer[i][j].Char.AsciiChar;
         n++;
      }
   str[n] = 0;
   return 1;
}

// This function will set the console's cursor position to c, which are the coordenates.
void gotoxy(int x, int y) {
   COORD coord;

   coord.X = x - 1; // Because of this, you can't set it to 0
   coord.Y = y - 1;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Incredible function. Wish I knew this back then in class
void puttext(int left, int top, int right, int bottom, char *str) {
   int i, j, n;
   SMALL_RECT r;
   CHAR_INFO buffer[25][80];

   memset(buffer, 0, sizeof(buffer));
   r = (SMALL_RECT){left - 1, top - 1, right - 1, bottom - 1};

   for (i = n = 0; i <= bottom - top; i++)
      for (j = 0; j <= right - left && str[n] != 0; j++) {
         buffer[i][j].Char.AsciiChar = str[n];
         buffer[i][j].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
         n++;
      }

   WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),
                      (CHAR_INFO *)buffer, (COORD){80, 25},
                      (COORD){0, 0}, &r);
}

// Wish they added some comments to this, so I know the different types.
void _setcursortype(int type) {
   CONSOLE_CURSOR_INFO Info;

   if (type)
      Info.dwSize = type;
   else {
      Info.bVisible = 0;
      Info.dwSize = 100;
   }

   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),
                        &Info);
}

// It seems to give attributes to the text "selected".
void textattr(int _attr) {
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}

void textbackground(int color) {
   __BACKGROUND = color;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                           __FOREGROUND + (color << 4));
}

// Most used function by me (Set the color to default in a "TUI")
void textcolor(int color) {
   __FOREGROUND = color;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                           color + (__BACKGROUND << 4));
}

// Gues it returns the Cursor position. X axis
int wherex() {
   CONSOLE_SCREEN_BUFFER_INFO info;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
   return info.dwCursorPosition.X + 1;
}

// Get it returns the cursor position. Y axis
int wherey() {
   CONSOLE_SCREEN_BUFFER_INFO info;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
   return info.dwCursorPosition.Y + 1;
}

#ifdef __cplusplus
}
#endif

#endif /* _CONIO_C_ */
