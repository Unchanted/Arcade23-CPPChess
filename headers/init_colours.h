    
#include <ncurses.h>
#ifndef INIT_COLOURS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define INIT_COLOURS_H

// making colours name extern so tat any file can access colours
extern int WOG_PAIR;
extern int WOW_PAIR;
extern int BOG_PAIR;
extern int BOW_PAIR;
extern int BOTW_PAIR;
extern int DGREYBG_PAIR;
extern int LGREYBG_PAIR;
extern int TWBG_PAIR;
extern int WOB_PAIR;
extern int WOR_PAIR;
extern int WOGN_PAIR;
extern int WOLY_PAIR;
extern int WODY_PAIR;
extern int BODY_PAIR;
extern int BOLY_PAIR;
extern int DYBG_PAIR;
extern int LYBG_PAIR;
void init_colours();
#endif
