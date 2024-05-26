#pragma once
#ifndef AI_H
#define AI_H

#include "Board.h"

class AI {
private:
    char color;
    int evaluation(Board& _board, char color);
public:
    AI(char _color);
    int miniMax(Board& board, int depth, bool maximizingPlayer, int alpha, int beta);
    Move getBestMove(Board& board, int depth);
};

#endif