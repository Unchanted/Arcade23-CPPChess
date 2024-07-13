#include "main.h"
#include <locale.h>
#include <ncurses.h>
#include <iostream>
#include "init_win.h"
#include "movement.h"

using namespace std;

WINDOW* board;
WINDOW* input;
char map[8][8][2];

int main() {
    
    setlocale(LC_ALL, "");
    initscr(); /* Start curses mode 		  */
    start_color();
    
    const int board_width = 84, board_height = 42;
    board = newwin(board_height, board_width, 0, 0);
    const int input_width = 45, input_height = 16;
    input = newwin(input_height, input_width, 0, 86);

    init_win();
    movement();

    endwin(); /* End curses mode		  */
    return 0;
}
