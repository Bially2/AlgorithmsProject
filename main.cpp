#include "Board.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    Board board;

    while (std::getline(std::cin, line)) {
        for (char c : line) {
            if ( c != '-' ) {
                board.counterHex(c);
            }
        }
        if (line == "IS_BOARD_CORRECT") {
            board.isBoardCorrectFunc();
        }
        if (line=="BOARD_SIZE"){
            std::cout<< board.boardSize()<<std::endl;
        }
        if (line=="PAWNS_NUMBER"){
            board.pawnNumbers();}
        if (line == "IS_GAME_OVER") {
            board.initializeBoard();
            board.fillBoard();
            board.checkGameOver();
            board.deleteBoard();
        }
        if (line == "IS_BOARD_POSSIBLE") {
            board.initializeBoard();
            board.fillBoard();
            if (board.isBoardPossible()) {
                std::cout << "YES" << std::endl;
            } else {
                std::cout << "NO" << std::endl;
            }
            board.deleteBoard();
        }
        if (line==("CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")) {
            board.initializeBoard();
            board.fillBoard();
            board.naive('r', 1);

        }
        if (line=="CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
            board.fillBoard();
            board.naive('b', 1);

        }
        if (line==("CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT")) {
            board.fillBoard();
            board.naive('r', 2);
        }
        if (line=="CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
            board.fillBoard();
            board.naive('b', 2);
            board.deleteBoard();
        }
    }

    return 0;
}