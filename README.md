# Conio library - Linux compatibility

This project is oriented to recreate all the abilities of conio without having to make workarounds, adding more compatibility to the library itself

Right now is under low development, since this is just a personal hobby project. Keep in mind, the original developers code will be left intact, unless I'm forced to change it.

## Objective

As it mentioned before, it is meant to allow Linux/Mac users be able to just install and run conio.h without having to seek external workarounds leading to overcomplications.

## Functions documentation and usage

### `void clrscr();`

This clear the screen.

### `void clreol();`

Clear to end of line, it blanks from the cursor to the right edge of the current line/row.

### `void delline();`

Clear an entire line/row, instead than starting from the cursor's position.

## Deprecated / Replaced functions.

### `void puttext(int left, int top, int right, int bottom, int char *str);`

Used to set a text in an specific position.
