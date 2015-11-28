#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "board.h"

int minimax_p1(const board *b, unsigned short depth, int alpha, int beta);
int minimax_p2(const board *b, unsigned short depth, int alpha, int beta);

direction best_move(const board *b, unsigned short depth);

#endif // _SEARCH_H_