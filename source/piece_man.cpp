#include <ncurses.h>
#include "../headers/calc.h"
#include "../headers/init_colours.h"
#include "../headers/main.h"
#include "../headers/piece.h"
#include "../headers/write.h"
using namespace std;

void print_piece(int y, int x, char color, char piece);
void remove_piece(int y, int x);

// Function to determine the attribute based on mode and color
int get_attribute(int y, int x, char color, char mode) {
    if (mode == 'w') {
        return (x + y) % 2 ? (color == 'w' ? WOG_PAIR : BOG_PAIR)
                           : (color == 'w' ? WOW_PAIR : BOW_PAIR);
    } else if (mode == 'h') {
        return (x + y) % 2 ? (color == 'w' ? WODY_PAIR : BODY_PAIR)
                           : (color == 'w' ? WOLY_PAIR : BOLY_PAIR);
    }
    return 0;  // Default return to avoid undefined behavior
}

// Function to print the piece
// It also adds the piece info in the main map array
void print_piece(int y, int x, char color, char piece, char mode, bool up_map) {
    int atr = get_attribute(y, x, color, mode);

    // Write the piece string array which consists of five lines
    for (size_t i = 0; i < 5; i++) {
        write(board, atr, y_axis(y) + i, x_axis(x), return_piece(piece)[i].c_str());
    }

    wrefresh(board);

    // Updating info in the main map
    if (up_map) {
        map[y - 1][x - 1][0] = color;
        map[y - 1][x - 1][1] = piece;
    }
}

// Function to remove the piece, it will also update value
// in the main array map of pieces
void remove_piece(int y, int x, char mode, bool up_map) {
    // Determine the attribute based on mode
    int atr = mode == 'w' ? ((x + y) % 2 ? DGREYBG_PAIR : LGREYBG_PAIR)
                          : ((x + y) % 2 ? DYBG_PAIR : LYBG_PAIR);

    // Print the background consisting of five lines
    for (size_t i = 0; i < 5; i++) {
        write(board, atr, y_axis(y) + i, x_axis(x), "██████████");
    }

    wrefresh(board);

    // Update the current info in the main map array
    if (up_map) {
        map[y - 1][x - 1][0] = '-';
        map[y - 1][x - 1][1] = '-';
    }
}
