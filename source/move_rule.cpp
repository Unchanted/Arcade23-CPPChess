#include <ncurses.h>
#include <cmath>
#include "../headers/calc.h"
#include "../headers/init_colours.h"
#include "../headers/main.h"
#include "../headers/obs_rec.h"
#include "../headers/piece_man.h"
#include "../headers/write.h"

bool check_empty(char color, char name);
bool check_same_col(char color1, char color2);
bool check_pawn(char from[], char to[]);
bool check_knight(char from[], char to[]);
bool check_queen(char from[], char to[]);
bool check_king(char from[], char to[]);
bool check_bishop(char from[], char to[]);
bool check_rook(char from[], char to[]);
bool check_legal(char from[], char to[]);

// check wehter the colour or the name is empty
bool check_empty(char color, char name) {
    if (color == '-' || name == '-') {
        write(input, WOR_PAIR, 7, 1, "No piece available at this position");
        return false;
    }
    return true;
}

// check wether the color of from position and to postion is the same or not
bool check_same_col(char color1, char color2) {
    if (color1 == color2) {
        write(input, WOR_PAIR, 7, 1, "Can't attack on the same color");
        return false;
    }
    return true;
}

// check wether the move is legal for a pawn
bool check_pawn(char from[], char to[]) {
    static bool first_move;
    static char en_passant[2];
    bool promo = false;
    int forward = 1;

    char color = get_col(from);
    bool is_white = (color == 'w');

    // Handle first move and en passant
    if ((is_white && y_cord(from) == 7) || (!is_white && y_cord(from) == 2)) {
        first_move = true;
        en_passant[0] = to[0];
        en_passant[1] = to[1];
        forward = 2;
    } else {
        first_move = false;
    }

    // En passant logic
    if (first_move) {
        first_move = false;
        if (abs(y_cord(en_passant) - y_cord(to)) == 1 &&
            x_cord(en_passant) == x_cord(to) &&
            abs(x_cord(en_passant) - x_cord(from)) == 1 &&
            y_cord(en_passant) == y_cord(from)) {
            
            write(input, WOGN_PAIR, 7, 1, "EN PASSANT move ");
            int remove_y = (is_white) ? y_cord(to) - 1 : y_cord(to) + 1;
            remove_piece(remove_y, x_cord(to), 'w', 1);
            return true;
        }
    }

    // Move legality check
    if (is_white) {
        if (y_cord(from) - y_cord(to) > forward) {
            write(input, WOR_PAIR, 7, 1, "Can not move more than one piece");
            return false;
        }
        if (y_cord(to) == 1) promo = true;
    } else {
        if (y_cord(to) - y_cord(from) > forward) {
            write(input, WOR_PAIR, 7, 1, "Can not move more than one piece");
            return false;
        }
        if (y_cord(to) == 8) promo = true;
    }

    // Straight move
    if (x_cord(from) == x_cord(to)) {
        if (get_col(to) != '-') {
            write(input, WOR_PAIR, 7, 1, "Can not attack from the front");
            return false;
        }
    } else if (abs(x_cord(from) - x_cord(to)) > 1 || get_col(to) == '-') {
        write(input, WOR_PAIR, 7, 1, "Can not move here");
        return false;
    }

    // Promotion logic
    if (promo) {
        write(input, BOTW_PAIR, 7, 1, "Enter q r n or b");
        char choice[1];
        wattron(input, COLOR_PAIR(WOG_PAIR));
        mvwgetnstr(input, 9, 1, choice, 1);

        while (choice[0] != 'q' && choice[0] != 'r' && choice[0] != 'n' && choice[0] != 'b') {
            write(input, WOG_PAIR, 9, 1, "   ");
            write(input, WOR_PAIR, 8, 1, "Please enter correct piece");
            wattron(input, COLOR_PAIR(WOG_PAIR));
            mvwgetnstr(input, 9, 1, choice, 1);
        }
        wattroff(input, COLOR_PAIR(WOG_PAIR));
        map[y_cord(from) - 1][x_cord(from) - 1][1] = choice[0];
    }
    return true;
}

// checking if queen move is legal or not
bool check_queen(char from[], char to[]) {
    if (!(check_rook(from, to) || check_bishop(from, to))) {
        write(input, WOR_PAIR, 7, 1, "QUEEN can not move in this way");
        return false;
    }
    write(input, WOG_PAIR, 7, 1, "                                  ");
    return true;
}

// check wether knight move is legal or not
bool check_knight(char from[], char to[]) {
    if (abs(y_cord(from) - y_cord(to)) > 2 ||
        abs(x_cord(from) - x_cord(to)) > 2 ||
        abs(y_cord(from) - y_cord(to)) == abs(x_cord(from) - x_cord(to)) ||
        abs(y_cord(from) - y_cord(to)) == 0 ||
        abs(x_cord(from) - x_cord(to)) == 0) {
        write(input, WOR_PAIR, 7, 1, "Knight can not move in this way");
        return false;
    }
    return true;
}

// check wether bishop move is legal or not
bool check_bishop(char from[], char to[]) {
    if (abs(x_cord(from) - x_cord(to)) != abs(y_cord(from) - y_cord(to))) {
        write(input, WOR_PAIR, 7, 1, "Bishop can not move in this way");
        return false;
    }
    return true;
}

// check wether rook move is legal or not
bool check_rook(char from[], char to[]) {
    if (x_cord(from) != x_cord(to) && y_cord(from) != y_cord(to)) {
        write(input, WOR_PAIR, 7, 1, "Rook can not move in this way");
        return false;
    }
    return true;
}

// check wether king move is legal or not
bool check_king(char from[], char to[]) {
    if (abs(y_cord(from) - y_cord(to)) > 1 || abs(x_cord(from) - x_cord(to)) > 1) {
        write(input, WOR_PAIR, 7, 1, "King can not move in this way");
        return false;
    }
    return true;
}

// taking the movement and checking legal moves depending on the piece
bool check_legal(char from[], char to[]) {
    switch (get_name(from)) {
        case 'p':
            return check_pawn(from, to) && check_path(from, to);
        case 'k':
            return check_king(from, to);
        case 'q':
            return check_queen(from, to) && check_path(from, to);
        case 'b':
            return check_bishop(from, to) && check_path(from, to);
        case 'n':
            return check_knight(from, to);
        case 'r':
            return check_rook(from, to) && check_path(from, to);
    }
    return false;
}
