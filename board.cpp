#include "Board.h"

Board::Board() :  sizecounter(0),sizeHex(0),redPawnsCounter(0), bluePawnsCounter(0),isAngle(false),spacecount(0) {}


void Board::counterHex(char c) {
    if (c == '<') {
        isAngle= true;
        sizecounter++;  //licznik do wielkosci planszy
    }
    if (c=='>'){
        if (spacecount==2){      //jesli pomiedzy <> sa dwie spacje to oznacza ze w srodku jest r albo b wiec nic z tym nie rob
            spacecount=0;         //zerowanie licznika
        }
        isAngle=false;
    }
    if (isAngle){
        if(c==' '){
            spacecount++;
        }
    }
    if (spacecount==3){
        boardCharacters.push_back('s');    //s--->space puste pole
        spacecount=0;
    }

    if (c == 'r') {
        redPawnsCounter++;
        boardCharacters.push_back(c);
    }
    else if (c == 'b') {
        bluePawnsCounter++;
        boardCharacters.push_back(c);
    }

}


void Board::pawnNumbers(){
    std::cout << redPawnsCounter + bluePawnsCounter << std::endl;       //suma wszystkich pionkow
    resetCounter();

}


int Board::boardSize(){

    sizecounter = static_cast<int>(sqrt(sizecounter));      //pierwsiatek z licznika daje sizeHexa
    return sizecounter;

}
void Board::isBoardCorrectFunc() {
    if (IS_BOARD_CORRECT) {                                 //sprawdza czy ilosc pionkow na planszy sie zgadza
        std::cout << "YES" << std::endl << std::endl;
    } else {
        std::cout << "NO" << std::endl << std::endl;
    }
    resetCounter();
}

void Board::initializeBoard() {                                 //inicjalizuje tablice dynamiczna w ktorej z inputa przekladam tutaj wartosci

    sizeHex = boardSize();
    hex_board = new char*[sizeHex];
    for (int i = 0; i < sizeHex; ++i) {
        hex_board[i] = new char[sizeHex]();
    }


}

void Board::deleteBoard() {                                     //usuwanie tablicy dynamicznej
    if (hex_board) {
        for (int i = 0; i < sizeHex; ++i) {

            delete[] hex_board[i];
        }
        delete[] hex_board;
        hex_board = nullptr;
    }
    resetCounter();

}


void Board::fillBoard() {
    int idx = 0;
    for (int start_col = 0; start_col < sizeHex; ++start_col) {
        for (int c = start_col, r = 0; c >= 0 && r < sizeHex; --c, ++r) {
            hex_board[c][r] = boardCharacters[idx++];
        }
    }
    for (int start_row = 1; start_row < sizeHex; ++start_row) {
        for (int c = sizeHex - 1, r = start_row; c >= 0 && r < sizeHex; --c, ++r) {
            hex_board[c][r] = boardCharacters[idx++];
        }
    }
    boardCharacters.clear();
}


bool Board::dfs(int r, int c, char player) {
    // Oznaczanie komórki jako odwiedzonej
    visited[r][c] = true;
    // Warunek zwycięstwa dla gracza
    if ((player == 'r' && c == sizeHex - 1) || (player == 'b' && r == sizeHex - 1)) {
        return true;
    }
    // Definicje przesunięć dla sześciu kierunków w heksie
    int row_offsets[] = {-1, 0, 1, 1, 0, -1};
    int col_offsets[] = {0, 1, 1, 0, -1, -1};

    // Sprawdzanie możliwości przejścia do każdego sąsiada
    for (int i = 0; i < 6; ++i) {
        int new_r = r + row_offsets[i];
        int new_c = c + col_offsets[i];
        // Sprawdzenie czy nowa komórka jest dostępna do przeszukania
        if (isValid(new_r, new_c) && !visited[new_r][new_c] && hex_board[new_r][new_c] == player) {
            if (dfs(new_r, new_c, player)) {
                return true;
            }
        }
    }

    return false;
}

bool Board::isValid(int r, int c) const {
    return r >= 0 && r < sizeHex && c >= 0 && c < sizeHex;      //sprawdza czy nowe koordynaty nie wyszly pozamape
}
bool Board::isGameOver(char player) {
    visited.assign(sizeHex, std::vector<bool>(sizeHex, false));     //inicjalizacja vectora polami false
    for (int i = 0; i < sizeHex; ++i) {
        if (player == 'r' && hex_board[i][0] == player && !visited[i][0]) {            //warunki rozpoczecia sprawdzania sciezki dla czerwonego gracza
            if (dfs(i, 0, player)) {                                              //czerwony musi przejsc z jednego konca wiersza na drugi
                return true;
            }
        }
        if (player == 'b' && hex_board[0][i] == player && !visited[0][i]) {           //warunki sprawdzania ciezki dla niebieskiego gracza musi przejsc od poczatku do konca kolumny
            if (dfs(0, i, player)) {                                            //jezeli dfs jest true to znalazlo sciezkie i jest game over
                return true;
            }
        }
    }

    return false;

}
void Board::checkGameOver() {
    if (IS_BOARD_CORRECT){
        if (isGameOver('r')) {
            std::cout << "YES RED" << std::endl;
        }
        else if (isGameOver('b')) {
            std::cout << "YES BLUE" << std::endl;
        }
        else {
            std::cout << "NO" << std::endl;
        }
    }
    else{
        std::cout << "NO" << std::endl;
    }
    visited.clear();
    resetCounter();
}
bool Board::isBoardPossible() {
    if (IS_BOARD_CORRECT) {
        if (isGameOver('r')) {

            if (redPawnsCounter - 1 == bluePawnsCounter) {
                for (int r = 0; r < sizeHex; ++r) {
                    for (int c = 0; c < sizeHex; ++c) {
                        if (hex_board[r][c] == 'r') {
                            hex_board[r][c] = 's';
                            redPawnsCounter--;
                            if (!isGameOver('r')) {
                                return true;
                            }
                            hex_board[r][c] = 'r';
                            redPawnsCounter++;
                        }
                    }
                }
            }

        }
        else if (isGameOver('b')) {
            if (redPawnsCounter == bluePawnsCounter) {
                for (int r = 0; r < sizeHex; ++r) {
                    for (int c = 0; c < sizeHex; ++c) {
                        if (hex_board[r][c] == 'b') {
                            hex_board[r][c] = 's';
                            bluePawnsCounter--;
                            if (!isGameOver('b')) {
                                return true;
                            }
                            hex_board[r][c] = 'b';
                            bluePawnsCounter++;
                        }
                    }
                }
            }

        }
        else
            return true;
    }
    return false;
}
void Board::naive(char player,int size) {
    if (isGameOver('r') || isGameOver('b')) {
        std::cout << "NO" << std::endl;
        return;
    }
    if (!isBoardPossible()){
        std::cout << "NO" << std::endl;
        return;
    }
    int clear_position = sizeHex * sizeHex - (bluePawnsCounter + redPawnsCounter);
    if (redPawnsCounter == bluePawnsCounter) {
        if (size == 1) {
            if (player == 'r') {
                if (clear_position >= 1) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;
                    } else {
                        std::cout << "NO " << std::endl;
                    }
                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }

            }
            if (player == 'b') {
                if (clear_position >= 2) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;
                    } else {
                        std::cout << "NO" << std::endl;
                    }

                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }
            }
        } else if (size == 2) {
            if (player == 'r') {
                if (clear_position >= 3) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;
                    } else {
                        std::cout << "NO" << std::endl;
                    }
                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }

            }
            if (player == 'b') {
                if (clear_position >= 4) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;
                    } else {
                        std::cout << "NO" << std::endl;
                    }

                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }
            }
        }
    }
    if (redPawnsCounter - 1 == bluePawnsCounter) {//niebieskiego kolej
        if (size == 1) {
            if (player == 'r') {
                if (clear_position >= 2) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;

                    } else {
                        std::cout << "NO" << std::endl;

                    }
                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }

            }
            if (player == 'b') {
                if (clear_position >= 1) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;
                    } else {
                        std::cout << "NO" << std::endl;
                    }
                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }
            }
        } else if (size == 2) {
            if (player == 'r') {
                if (clear_position >= 4) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;
                    } else {
                        std::cout << "NO" << std::endl;
                    }
                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }

            }
            if (player == 'b') {
                if (clear_position >= 3) {
                    if (WinInMoves(player, size)) {
                        std::cout << "YES" << std::endl;
                    } else {
                        std::cout << "NO" << std::endl;
                    }
                } else {
                    std::cout << "NO" << std::endl;
                    return;
                }
            }
        }

    }
}
bool Board::WinInMoves(char player, int moves) {
    for (int r1 = 0; r1 < sizeHex; ++r1) {
        for (int c1 = 0; c1 < sizeHex; ++c1) {
            if (hex_board[r1][c1] == 's') {  // pierwszy ruch
                hex_board[r1][c1] = player;
                if (moves == 1 && isGameOver(player)) { //jesli INONE i znalazlo rezultat to zwracamy true
                    hex_board[r1][c1] = 's';    //cofniecie ruchu
                    return true;
                }

                if (moves == 2) {
                    for (int r2 = 0; r2 < sizeHex; ++r2) {          //wczytanie drugie posuniecia
                        for (int c2 = 0; c2 < sizeHex; ++c2) {
                            if (hex_board[r2][c2] == 's' && !(r1 == r2 && c1 == c2)) {  // Sprawdzamy drugi ruch
                                hex_board[r2][c2] = player;
                                if (isGameOver(player)) {  // Gracz wygrywa dwoma ruchami
                                    hex_board[r1][c1] = 's'; // Usuń pierwszy pionek
                                    if (!isGameOver(player)) {  // Nie wygrywa bez pierwszego pionka
                                        hex_board[r2][c2] = 's'; // Usuń drugi pionek
                                        return true;
                                    }
                                    hex_board[r1][c1] = player; //pierwszy pionek wraca
                                    hex_board[r2][c2] = 's'; // Usuń drugi pionek
                                    //sprawdz znowu co sie stanie
                                    if (!isGameOver(player)) {  // Nie wygrywa bez drugiego pionka
                                        hex_board[r2][c2] = 's'; // Przywróć drugi pionek
                                        return true;
                                    }
                                    hex_board[r2][c2] = player; // Przywróć drugi pionek
                                }
                                hex_board[r2][c2] = 's'; // Cofnij drugi ruch
                            }
                        }
                    }
                }
                hex_board[r1][c1] = 's'; // Cofnij pierwszy ruch
            }
        }
    }
    return false; //nie znalazlo w ogole
}

void Board::resetCounter() {
    sizeHex=0;
    sizecounter=0;
    redPawnsCounter = 0;
    bluePawnsCounter = 0;
    boardCharacters.clear();
}

Board::~Board(){
    deleteBoard();
}


