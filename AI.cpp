#include "AI.h"
#include <limits>
#include <algorithm>
#include <cctype>  // Добавьте эту строку

AI::AI(char _color) : color(_color) {}

int AI::evaluation(Board& _board, char color) {
    int score = 0;
    // Пример логики оценки состояния доски
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (_board.board[y][x] == color) {
                score += 100; // Базовая стоимость шашки
                // Добавление условий для оценки позиций на доске
            }
            else if (_board.board[y][x] == toupper(color)) {
                score += 250; // Стоимость дамки
                // Добавление условий для оценки позиций дамок
            }
            else if (_board.board[y][x] != ' ' && _board.board[y][x] != color && _board.board[y][x] != toupper(color)) {
                score -= 100; // Штраф за шашку противника
            }
        }
    }
    return score;
}

int AI::miniMax(Board& board, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0) {
        return evaluation(board, color);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (auto& move : board.getMoves(color)) {
            Board newBoard = board.getNewBoard(move, color);
            int eval = miniMax(newBoard, depth - 1, false, alpha, beta);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        char opponentColor = (color == 'w') ? 'b' : 'w';
        for (auto& move : board.getMoves(opponentColor)) {
            Board newBoard = board.getNewBoard(move, opponentColor);
            int eval = miniMax(newBoard, depth - 1, true, alpha, beta);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

Move AI::getBestMove(Board& board, int depth) {
    int maxEval = std::numeric_limits<int>::min();
    Move bestMove(0, 0, 0, 0);
    for (auto& move : board.getMoves(color)) {
        Board newBoard = board.getNewBoard(move, color);
        int eval = miniMax(newBoard, depth - 1, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        if (eval > maxEval) {
            maxEval = eval;
            bestMove = move;
        }
    }
    return bestMove;
}