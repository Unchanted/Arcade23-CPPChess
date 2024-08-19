#include <ncurses.h>
#include "../headers/calc.h"
#include "../headers/init_colours.h"
#include "../headers/main.h"
#include "../headers/move_piece.h"
#include "../headers/move_rule.h"
#include "../headers/score.h"
#include "../headers/write.h"
#include "../headers/history.h"

void movement();
void ask_cordinates(int y, int x, char* cord);

// ask user if he wants to continue or not
// and refresh the info board
char refresh_turn() {
    write(input, WOG_PAIR, 10, 1, "Press enter to continue or q to quit");
    char choice[1];
    wattron(input, COLOR_PAIR(WOG_PAIR));
    mvwgetnstr(input, 11, 1, choice, 1);
    werase(input);
    box(input, 0, 0);
    wrefresh(input);
    wattroff(input, COLOR_PAIR(WOG_PAIR));
    return choice[0];
}

// function to ask coordinates from the user to move
void ask_cordinates(int y, int x, char* cord) {
    wattron(input, COLOR_PAIR(WOG_PAIR));
    mvwgetnstr(input, y, x, cord, 2);
    
    // error handling for the user to enter the right coordinates
    while (cord[1] < '1' || cord[1] > '9' || cord[0] < 'a' || cord[0] > 'h') {
        write(input, WOG_PAIR, y, x, "   ");
        write(input, WOR_PAIR, y - 1, 1, "Please enter correct coordinates");
        mvwgetnstr(input, y, x, cord, 2);
    }
    wattroff(input, COLOR_PAIR(WOG_PAIR));
}

// movement function that manages moving, asking pieces, etc., and updating the info table
void movement() {
    char from[3] = {'\0'};
    char to[3] = {'\0'};
    bool current_turn = true; // white for true and black for false
    int turn_ln = 1;
    int turn_no = 1;
    time_t now = time(0);
    tm* start_time = localtime(&now);
    curs_set(1);

    while (1) {
        if (refresh_turn() == 'q') {
            break;
        }

        // displaying current player turn on the info board
        write(info, get_turn_col(current_turn), 1, 33, "          ");
        write(info, get_turn_col(current_turn), 2, 33, "   TURN   ");
        write(info, get_turn_col(current_turn), 3, 33, "          ");

        // asking which piece the user wants to move
        write(input, WOG_PAIR, 1, 1, "Which piece do you wanna move");
        ask_cordinates(3, 1, from);

        // checking if the piece is empty or not
        if (!check_empty(get_name(from), get_col(from))) {
            continue;
        }

        // check if it's the turn of the piece chosen or not
        if (col_bool(get_col(from)) != current_turn) {
            write(input, WOR_PAIR, 7, 1, "It's not your turn");
            continue;
        }

        // asking where the user wants to move the piece
        write(input, WOG_PAIR, 4, 1, "Where do you want to move it");
        ask_cordinates(6, 1, to);

        // check if the move was legal and successful
        if (move_piece(from, to)) {

            // reprint from line 1 if the info board becomes full
            if (turn_ln > 22) {
                turn_ln = 1;
            }

            // writing the current move in the info board
            write_hstr(start_time, turn_ln, turn_no, to, current_turn, from);

            // updating the score
            if (score('w') > 0) {
                write(info, BOTW_PAIR, 12, 23, "                    ");
                write(info, BOTW_PAIR, 13, 23, " WHITE WINNING : +%d ", score('w'));
                write(info, BOTW_PAIR, 14, 23, "                    ");
            } else if (score('b') > 0) {
                write(info, WOB_PAIR, 12, 23, "                    ");
                write(info, WOB_PAIR, 13, 23, " BLACK WINNING : +%d ", score('b'));
                write(info, WOB_PAIR, 14, 23, "                    ");
            } else {
                write(info, WOW_PAIR, 12, 23, "                    ");
                write(info, WOW_PAIR, 13, 23, "        DRAW        ");
                write(info, WOW_PAIR, 14, 23, "                    ");
            }

            // changing the turn color
            current_turn = !current_turn;

            // incrementing current line and turn number
            turn_ln++;
            turn_no++;
        }
    }
}
