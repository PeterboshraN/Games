
#ifndef ULTIMATEX_O_H
#define ULTIMATEX_O_H

#include "BoardGame_Classes.h"

template <typename T>
class UltimateBoard:public Board<T> {
public:
    UltimateBoard();
    bool update_board (int x , int y , T symbol) override;
    void display_board () override;
    bool is_win() override;
    bool is_draw()override;
    bool game_is_over()override;


};

template <typename T>
class UltimatePlayer : public Player<T> {
public:
    UltimatePlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class UltimateRandomPlayer : public RandomPlayer<T>{
public:
    UltimateRandomPlayer (T symbol);
    void getmove(int &x, int &y) ;
};




//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;

// Constructor for X_O_Board
template <typename T>
UltimateBoard<T>::UltimateBoard() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool UltimateBoard<T>::update_board(int x, int y, T mark)  {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void UltimateBoard<T>::display_board() {
    cout << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->board[i][j] == 0) {
                cout << "| (" << i << ", " << j << ") ";
            } else {
                cout << "|   " << this->board[i][j] << "    ";
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
}

template <typename T>
bool UltimateBoard<T>::is_win() {
    // Meta-board to track the status of each 3x3 sub-board
    vector<vector<T>> smallBoard(3, vector<T>(3, 0));

    // Check each 3x3 sub-board
    for (int smallRow = 0; smallRow < 3; ++smallRow) {
        for (int smallCol = 0; smallCol < 3; ++smallCol) {
            int startX = smallRow * 3;
            int startY = smallCol * 3;

            // Check rows, columns, and diagonals within the sub-board
            for (int i = 0; i < 3; ++i) {
                // Check rows
                if (this->board[startX + i][startY] != 0 &&
                    this->board[startX + i][startY] == this->board[startX + i][startY + 1] &&
                    this->board[startX + i][startY + 1] == this->board[startX + i][startY + 2]) {
                    smallBoard[smallRow][smallCol] = this->board[startX + i][startY];
                }

                // Check columns
                if (this->board[startX][startY + i] != 0 &&
                    this->board[startX][startY + i] == this->board[startX + 1][startY + i] &&
                    this->board[startX + 1][startY + i] == this->board[startX + 2][startY + i]) {
                    smallBoard[smallRow][smallCol] = this->board[startX][startY + i];
                }
            }

            // Check diagonals
            if (this->board[startX][startY] != 0 &&
                this->board[startX][startY] == this->board[startX + 1][startY + 1] &&
                this->board[startX + 1][startY + 1] == this->board[startX + 2][startY + 2]) {
                smallBoard[smallRow][smallCol] = this->board[startX][startY];
            }

            if (this->board[startX][startY + 2] != 0 &&
                this->board[startX][startY + 2] == this->board[startX + 1][startY + 1] &&
                this->board[startX + 1][startY + 1] == this->board[startX + 2][startY]) {
                smallBoard[smallRow][smallCol] = this->board[startX][startY + 2];
            }
        }
    }

    // Check rows, columns, and diagonals on the meta-board
    for (int i = 0; i < 3; ++i) {
        // Check rows
        if (smallBoard[i][0] != 0 &&
            smallBoard[i][0] == smallBoard[i][1] &&
            smallBoard[i][1] == smallBoard[i][2]) {
            return true;
        }

        // Check columns
        if (smallBoard[0][i] != 0 &&
            smallBoard[0][i] == smallBoard[1][i] &&
            smallBoard[1][i] == smallBoard[2][i]) {
            return true;
        }
    }

    // Check diagonals
    if (smallBoard[0][0] != 0 &&
        smallBoard[0][0] == smallBoard[1][1] &&
        smallBoard[1][1] == smallBoard[2][2]) {
        return true;
    }

    if (smallBoard[0][2] != 0 &&
        smallBoard[0][2] == smallBoard[1][1] &&
        smallBoard[1][1] == smallBoard[2][0]) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool UltimateBoard<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool UltimateBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
UltimatePlayer<T>::UltimatePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void UltimatePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
UltimateRandomPlayer<T>::UltimateRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void UltimateRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 9;
    y = rand() % 9;
}




#endif

