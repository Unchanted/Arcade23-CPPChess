#ifndef HISTORY_H  // To make sure you don't declare the function more th
#define HISTORY_H
#include <iostream>
using namespace std;
void write_hstr(tm* start_time ,int turn_ln,
                int turn_no,
                char* to,
                bool current_turn,
                char* from);

#endif
