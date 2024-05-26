#include <iostream>
#include <string>
#include "Board.h"
#include "AI.h"

int main() {
    setlocale(LC_ALL, "ru");
    Board game;
    AI ai('b');
    game.printBoard();

    while (true) {
        std::vector<Move> possibleMoves = game.getMoves('w');
        if (possibleMoves.empty()) {
            std::cout << "ИИ выиграл!\n";
            break;
        }

        std::cout << "Возможные ходы:\n";
        for (size_t i = 0; i < possibleMoves.size(); ++i) {
            std::cout << i + 1 << ". " << char('a' + possibleMoves[i].x1) << 8 - possibleMoves[i].y1
                << " -> " << char('a' + possibleMoves[i].x2) << 8 - possibleMoves[i].y2 << "\n";
        }

        std::cout << "Чтобы сдаться, введите 'surrender'.\n";
        std::cout << "Выберите ход (введите номер): ";
        std::string moveChoice;
        std::cin >> moveChoice;

        // Проверяем, если игрок выбрал сдачу
        if (moveChoice == "surrender") {
            std::cout << "Вы сдались. ИИ победил!\n";
            break;
        }

        size_t moveIndex;
        try {
            moveIndex = std::stoi(moveChoice);
        }
        catch (const std::invalid_argument&) {
            std::cout << "Неверный ввод. Попробуйте еще раз.\n";
            continue;
        }

        if (moveIndex < 1 || moveIndex > possibleMoves.size()) {
            std::cout << "Неверный выбор. Попробуйте еще раз.\n";
            continue;
        }

        Move playerMove = possibleMoves[moveIndex - 1];
        game = game.getNewBoard(playerMove, 'w');
        game.printBoard();

        Move aiMove = ai.getBestMove(game, 5);
        game = game.getNewBoard(aiMove, 'b');
        std::cout << "ИИ сделал ход.\n";
        game.printBoard();

        if (game.getMoves('w').empty()) {
            std::cout << "ИИ выиграл!\n";
            break;
        }
        if (game.getMoves('b').empty()) {
            std::cout << "Вы выиграли!\n";
            break;
        }
    }

    return 0;
}