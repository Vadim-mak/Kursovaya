#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Move.h"

class Board {
public:
    char board[8][8];

    Board();
    bool isInsideBoard(int x, int y);
    std::vector<Move> getMoves(char color);
    Board getNewBoard(Move move, char color);
    void printBoard();
};

#endif