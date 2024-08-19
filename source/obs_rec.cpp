#include <ncurses.h>
#include <cmath>
#include "../headers/calc.h"
#include "../headers/init_colours.h"
#include "../headers/main.h"
#include "../headers/write.h"

// Check whether there is something in the path
// if the piece is moving straight or not
bool check_straight(char from[], char to[]) {
    int init, end;
    char cord;

    // Determine the axis of movement (straight in y or x axis)
    if (y_cord(from) == y_cord(to)) {
        cord = 'x';
        init = std::min(x_cord(from), x_cord(to));
        end = std::max(x_cord(from), x_cord(to));
    } else if (x_cord(from) == x_cord(to)) {
        cord = 'y';
        init = std::min(y_cord(from), y_cord(to));
        end = std::max(y_cord(from), y_cord(to));
    } else {
        return true; // Not moving straight
    }

    // Check each block along the path for any obstacles
    for (int i = init + 1; i < end; i++) {
        if (cord == 'x') {
            if (map[y_cord(from) - 1][i - 1][0] != '-') {
                write(input, WOR_PAIR, 7, 1, "Something on the way");
                return false;
            }
        } else if (cord == 'y') {
            if (map[i - 1][x_cord(from) - 1][0] != '-') {
                write(input, WOR_PAIR, 7, 1, "Something on the way");
                return false;
            }
        }
    }
    return true;
}

// Check whether there is something along the path
// depending if there is any piece in the path or not
bool check_diagnol(char from[], char to[]) {
    int x_step, y_step;
    size_t x, y;

    // Check if it's moving diagonally
    if (abs(y_cord(from) - y_cord(to)) == abs(x_cord(from) - x_cord(to))) {
        x_step = (x_cord(from) < x_cord(to)) ? 1 : -1;
        y_step = (y_cord(from) < y_cord(to)) ? 1 : -1;

        // Check each block along the diagonal path for any obstacles
        for (x = x_cord(from) + x_step, y = y_cord(from) + y_step;
             x != x_cord(to); x += x_step, y += y_step) {
            if (map[y - 1][x - 1][0] != '-') {
                write(input, WOR_PAIR, 7, 1, "Something on the way");
                return false;
            }
        }
    }
    return true;
}

bool check_path(char from[], char to[]) {
    return check_straight(from, to) && check_diagnol(from, to);
}
