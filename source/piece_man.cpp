#include <ncurses.h>
#include "../headers/calc.h"
#include "../headers/init_colours.h"
#include "../headers/main.h"
#include "../headers/piece.h"
#include "../headers/write.h"
using namespace std;

// Function to determine the attribute based on mode and color
int get_attribute(int y, int x, char color, char mode) {
    switch (mode) {
        case 'w':
            return (x + y) % 2 ? (color == 'w' ? WOG_PAIR : BOG_PAIR)
                               : (color == 'w' ? WOW_PAIR : BOW_PAIR);
        case 'h':
            return (x + y) % 2 ? (color == 'w' ? WODY_PAIR : BODY_PAIR)
                               : (color == 'w' ? WOLY_PAIR : BOLY_PAIR);
        default:
            return 0;  // Default return to avoid undefined behavior
    }
}

// Function to print the piece
// It also adds the piece info in the main map array
void print_piece(int y, int x, char color, char piece, char mode, bool up_map) {
    int atr = get_attribute(y, x, color, mode);

    // Write the piece string array which consists of five lines
    const string* piece_lines = return_piece(piece);
    for (size_t i = 0; i < 5; i++) {
        write(board, atr, y_axis(y) + i, x_axis(x), piece_lines[i].c_str());
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
    int atr = (x + y) % 2 ? (mode == 'w' ? DGREYBG_PAIR : DYBG_PAIR)
                          : (mode == 'w' ? LGREYBG_PAIR : LYBG_PAIR);

    // Print the background consisting of five lines
    const char* empty_line = "██████████";
    for (size_t i = 0; i < 5; i++) {
        write(board, atr, y_axis(y) + i, x_axis(x), empty_line);
    }

    wrefresh(board);

    // Update the current info in the main map array
    if (up_map) {
        map[y - 1][x - 1][0] = '-';
        map[y - 1][x - 1][1] = '-';
    }
}
