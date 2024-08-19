#include <ncurses.h>
#include "../headers/init_colours.h"
#include "../headers/main.h"
#include "../headers/piece_man.h"
#include "../headers/write.h"

void init_piece();
void init_board();
void init_input();
void init_win();
void init_bkg_brdr(WINDOW* win);
void init_info();
void init_title();
void init_inft();

// Function to initialize all the pieces with their initial positions according to chess rules
void init_piece() {
    const char pieces[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

    for (size_t i = 0; i < 8; i++) {
        print_piece(1, i + 1, 'b', pieces[i], 'w', 1);
        print_piece(8, i + 1, 'w', pieces[i], 'w', 1);
        print_piece(2, i + 1, 'b', 'p', 'w', 1);
        print_piece(7, i + 1, 'w', 'p', 'w', 1);
    }
}

// Function to set the board background and border
void init_bkg_brdr(WINDOW* win) {
    wbkgd(win, COLOR_PAIR(DGREYBG_PAIR));  // Set board background
    wattron(win, COLOR_PAIR(WOG_PAIR));    // Activate color pair
    box(win, 0, 0);                        // Draw border
    wrefresh(win);                         // Refresh the window
    wattroff(win, COLOR_PAIR(WOG_PAIR));   // Deactivate color pair
}

// Function to initialize the chess board
void init_board() {
    init_bkg_brdr(board);

    wattron(board, COLOR_PAIR(WOG_PAIR));

    // Print the axis on the board
    for (size_t i = 0; i < 8; i++) {
        mvwprintw(board, (i * 5) + 3, 83, "%d", 8 - i);
        mvwprintw(board, (i * 5) + 3, 0, "%d", 8 - i);
        mvwprintw(board, 0, (i * 10) + 6, "%c", 65 + i);
        mvwprintw(board, 41, (i * 10) + 6, "%c", 65 + i);
    }

    wrefresh(board);
    wattroff(board, COLOR_PAIR(WOG_PAIR));

    // Print the checkerboard pattern on the board
    for (size_t i = 0; i < 8; i++) {
        const int offset = (i % 2 == 0) ? 0 : 10;
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 1; k < 6; k++) {
                write(board, LGREYBG_PAIR, (i * 5) + k, (j * 20) + offset + 2, "██████████");
            }
        }
    }
}

// Function to initialize the input window
void init_input() {
    init_bkg_brdr(input);
}

// Function to initialize the info window
void init_info() {
    init_bkg_brdr(info);

    wattroff(info, COLOR_PAIR(WOG_PAIR));
    write(info, WOW_PAIR, 12, 23, "                    ");
    write(info, WOW_PAIR, 13, 23, "        DRAW        ");
    write(info, WOW_PAIR, 14, 23, "                    ");
}

// Function to initialize the title window
void init_title() {
    wbkgd(title, COLOR_PAIR(TWBG_PAIR));          // Set background
    wattron(title, COLOR_PAIR(BOTW_PAIR));        // Activate color pair
    box(title, 0, 0);                             // Draw border
    wrefresh(title);
    write(title, BOTW_PAIR, 1, 3, " CCC    H  H    EEEE     SSS      SSS  ");
    write(title, BOTW_PAIR, 2, 3, "C       H  H    E       S        S     ");
    write(title, BOTW_PAIR, 3, 3, "C       HHHH    EEE      SSS      SSS  ");
    write(title, BOTW_PAIR, 4, 3, "C       H  H    E           S        S ");
    write(title, BOTW_PAIR, 5, 3, " CCC    H  H    EEEE    SSSS     SSSS  ");
    wattroff(title, COLOR_PAIR(BOTW_PAIR));       // Deactivate color pair
}

// Function to initialize the info title window
void init_inft() {
    wbkgd(info_title, COLOR_PAIR(TWBG_PAIR));     // Set background
    wattron(info_title, COLOR_PAIR(BOTW_PAIR));   // Activate color pair
    box(info_title, 0, 0);                        // Draw border
    wrefresh(info_title);
    write(info_title, BOTW_PAIR, 1, 20, "INFO");
    wattroff(info_title, COLOR_PAIR(BOTW_PAIR));  // Deactivate color pair
}

// Function to initialize all windows
void init_win() {
    init_colours();
    refresh();

    // Call functions to initialize all windows
    init_title();
    init_board();
    init_input();
    init_info();
    init_inft();
    init_piece();

    // Initialize empty squares on the board where there are no pieces
    for (size_t i = 2; i < 6; i++) {
        for (size_t j = 0; j < 8; j++) {
            map[i][j][0] = '-';
            map[i][j][1] = '-';
        }
    }
}
