#ifndef GENERAL_H  // To make sure you don't declare the function more than
#define GENERAL_H
// once by including the header multiple times.

void write_input(int col, int y, int x, const char* fmt, ...);
void write_board(int col, int y, int x, const char* fmt, ...);
#endif
