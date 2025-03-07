// Board.h
#ifndef BOARD_H
#define BOARD_H
#define IS_BOARD_CORRECT (redPawnsCounter == bluePawnsCounter || redPawnsCounter - 1 == bluePawnsCounter)
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
class Board {
public:
    Board();
    int boardSize(); //"BOARD_SIZE"
    void isBoardCorrectFunc();//IS_CORRECT
    void pawnNumbers();//PAWN_NUMBERS
    void counterHex(char c);//LICZNIK PIONKOW/SIZE/WRZUCANIE DO VECTORA


    void initializeBoard();//INICJALIZACJA TABLICY
    void fillBoard();//WKLADANIE WARTOSCI DO TABLICY
    void deleteBoard();//USUWANIE TABLICY
    void resetCounter();

    //GAME_OVER ORAZ FUNKCJE SPRAWDZAJACE WYGRYWANIE
    bool dfs(int r, int c, char player);
    [[nodiscard]] bool isValid(int r, int c) const;
    bool isGameOver(char player);
    void checkGameOver();

    bool isBoardPossible(); //IS_BOARD_POSSIBLE

    //NAIVE
    void naive(char player, int size);
    bool WinInMoves(char player, int moves);
    ~Board();




private:
    char** hex_board{};
    std::vector<char> boardCharacters;
    std::vector<std::vector<bool>> visited;
    int sizecounter{};
    int sizeHex{};
    int redPawnsCounter;
    int bluePawnsCounter;
    int spacecount;
    bool isAngle;


};

#endif // BOARD_H