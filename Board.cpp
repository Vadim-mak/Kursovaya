#include "Board.h"
#include <iostream>
#include <cctype>

Board::Board() {
    char init_board[8][8] = {
        {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
        {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
        {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'w', ' ', 'w', ' ', 'w', ' ', 'w'},
        {'w', ' ', 'w', ' ', 'w', ' ', 'w', ' '},
        {' ', 'w', ' ', 'w', ' ', 'w', ' ', 'w'}
    };
    std::copy(&init_board[0][0], &init_board[0][0] + 8 * 8, &board[0][0]);
}

bool Board::isInsideBoard(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

std::vector<Move> Board::getMoves(char color) {
    std::vector<Move> moves;
    // ������ ������ ��� ����������� ��������� �����
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (board[y][x] == color || board[y][x] == toupper(color)) {
                // ��� ������� �����
                if (board[y][x] == color) {
                    // �������� ����������� ���� �� ���� ������ ������
                    int dir = (color == 'w') ? -1 : 1;
                    if (isInsideBoard(x + 1, y + dir) && board[y + dir][x + 1] == ' ') {
                        moves.push_back(Move(x, y, x + 1, y + dir));
                    }
                    if (isInsideBoard(x - 1, y + dir) && board[y + dir][x - 1] == ' ') {
                        moves.push_back(Move(x, y, x - 1, y + dir));
                    }
                    // ���������� ������ ��� ������� ����� �����
                    // �������� ����������� ������
                    if (isInsideBoard(x + 2, y + 2 * dir) &&
                        board[y + dir][x + 1] != ' ' &&
                        board[y + dir][x + 1] != color &&
                        board[y + dir][x + 1] != toupper(color) &&
                        board[y + 2 * dir][x + 2] == ' ') {
                        moves.push_back(Move(x, y, x + 2, y + 2 * dir, true));
                    }
                    if (isInsideBoard(x - 2, y + 2 * dir) &&
                        board[y + dir][x - 1] != ' ' &&
                        board[y + dir][x - 1] != color &&
                        board[y + dir][x - 1] != toupper(color) &&
                        board[y + 2 * dir][x - 2] == ' ') {
                        moves.push_back(Move(x, y, x - 2, y + 2 * dir, true));
                    }
                }
                // ��� �����
                if (board[y][x] == toupper(color)) {
                    // ����� ����� ��������� �� ����� ���������� ������ �� ���������
                    int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
                    for (auto& dir : directions) {
                        int dx = dir[0], dy = dir[1];
                        int curX = x, curY = y;
                        while (isInsideBoard(curX + dx, curY + dy) && board[curY + dy][curX + dx] == ' ') {
                            moves.push_back(Move(x, y, curX + dx, curY + dy));
                            curX += dx;
                            curY += dy;
                        }
                        // �������� ����������� ������
                        if (isInsideBoard(curX + 2 * dx, curY + 2 * dy) &&
                            board[curY + dy][curX + dx] != ' ' &&
                            board[curY + dy][curX + dx] != color &&
                            board[curY + dy][curX + dx] != toupper(color) &&
                            board[curY + 2 * dy][curX + 2 * dx] == ' ') {
                            // ������ ����� ����� ����������
                            moves.push_back(Move(x, y, curX + 2 * dx, curY + 2 * dy, true));
                            // ����� ������ ����� ����� ���������� ��������, ���� ��� ��������
                            int nextX = curX + 2 * dx;
                            int nextY = curY + 2 * dy;
                            while (isInsideBoard(nextX + dx, nextY + dy) && board[nextY + dy][nextX + dx] == ' ') {
                                moves.push_back(Move(x, y, nextX + dx, nextY + dy));
                                nextX += dx;
                                nextY += dy;
                            }
                        }
                    }
                }
            }
        }
    }
    return moves;
}

Board Board::getNewBoard(Move move, char color) {
    Board newBoard = *this;
    // ����������� �����
    newBoard.board[move.y1][move.x1] = ' ';
    newBoard.board[move.y2][move.x2] = (isupper(board[move.y1][move.x1])) ? toupper(color) : color;

    // ���� ��� ��� � �������, ������� ������� �����
    if (move.jump) {
        int midX = (move.x1 + move.x2) / 2;
        int midY = (move.y1 + move.y2) / 2;
        newBoard.board[midY][midX] = ' ';
    }

    // ���� ����� ��������� ���������������� ����, ��� ������������ � �����
    if (color == 'w' && move.y2 == 0) {
        newBoard.board[move.y2][move.x2] = 'W';
    }
    if (color == 'b' && move.y2 == 7) {
        newBoard.board[move.y2][move.x2] = 'B';
    }

    return newBoard;
}

void Board::printBoard() {
    std::cout << "  a b c d e f g h\n"; // ������� �����������
    for (int y = 0; y < 8; ++y) {
        std::cout << 8 - y << " "; // ������� �����������
        for (int x = 0; x < 8; ++x) {
            char piece = board[y][x];
            if (piece == 'w') {
                std::cout << "\033[31m" << piece << "\033[0m "; // ����� �����
            }
            else if (piece == 'W') {
                std::cout << "\033[31;1m" << piece << "\033[0m "; // ����� �����
            }
            else if (piece == 'b') {
                std::cout << "\033[36m" << piece << "\033[0m "; // ������ �����
            }
            else if (piece == 'B') {
                std::cout << "\033[36;1m" << piece << "\033[0m "; // ������ �����
            }
            else {
                std::cout << piece << " ";
            }
        }
        std::cout << " " << 8 - y << "\n"; // ������� �����������
    }
    std::cout << "  a b c d e f g h\n"; // ������ �����������
}