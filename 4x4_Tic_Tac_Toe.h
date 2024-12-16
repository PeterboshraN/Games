#ifndef FOURBYFOUR_TIC_TAC_TOE_H
#define FOURBYFOUR_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>
using namespace std;

// Global variables for new position
int new_x;
int new_y;

// Pointers to global variables
int* ptr_new_x = &new_x;
int* ptr_new_y = &new_y;

// FourByFourBoard Class
template <typename T>
class FourByFourBoard : public Board<T> {
public:
    FourByFourBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    vector<pair<int, int>> player1_tokens;
    vector<pair<int, int>> player2_tokens;
};

// FourByFourPlayer Class
template <typename T>
class FourByFourPlayer : public Player<T> {
public:
    FourByFourPlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

// RandomFourByFourPlayer Class
template <typename T>
class RandomFourByFourPlayer : public RandomPlayer<T> {
public:
    RandomFourByFourPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

//--------------------------------------- IMPLEMENTATION

#include <cmath>

// Constructor for FourByFourBoard
template <typename T>
FourByFourBoard<T>::FourByFourBoard() {
    this->rows = this->columns = 4;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '.';
        }
    }

    player1_tokens = {{0, 1}, {0, 3}, {3, 0}, {3, 2}};
    player2_tokens = {{0, 0}, {0, 2}, {3, 1}, {3, 3}};

    for (const auto& token : player1_tokens) {
        this->board[token.first][token.second] = 'X';
    }
    for (const auto& token : player2_tokens) {
        this->board[token.first][token.second] = 'O';
    }

    this->n_moves = 0;
}

// Update board state
template <typename T>
bool FourByFourBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != symbol) {
        return false;
    }

    if (*ptr_new_x < 0 || *ptr_new_x >= this->rows || *ptr_new_y < 0 || *ptr_new_y >= this->columns || this->board[*ptr_new_x][*ptr_new_y] != '.') {
        return false;
    }

    if (abs(x - *ptr_new_x) + abs(y - *ptr_new_y) != 1) {
        return false;
    }

    this->board[x][y] = '.';
    this->board[*ptr_new_x][*ptr_new_y] = symbol;
    this->n_moves++;
    return true;
}

// Display the board
template <typename T>
void FourByFourBoard<T>::display_board() {
    cout << "\n4x4 Tic-Tac-Toe Board with Positions:\n";
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            cout << this->board[i][j] << "(" << i << ", " << j << ") ";
        }
        cout << endl;
    }
}

// Check for win condition
template <typename T>
bool FourByFourBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != '.' && (
                    (j + 2 < this->columns && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2]) ||
                    (i + 2 < this->rows && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j]) ||
                    (i + 2 < this->rows && j + 2 < this->columns && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2]) ||
                    (i - 2 >= 0 && j + 2 < this->columns && this->board[i][j] == this->board[i - 1][j + 1] && this->board[i][j] == this->board[i - 2][j + 2]))) {
                return true;
            }
        }
    }
    return false;
}

// Check for draw condition
template <typename T>
bool FourByFourBoard<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

// Check if the game is over
template <typename T>
bool FourByFourBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for FourByFourPlayer
template <typename T>
FourByFourPlayer<T>::FourByFourPlayer(string name, T symbol) : Player<T>(name, symbol) {}

// Get move for FourByFourPlayer
template <typename T>
void FourByFourPlayer<T>::getmove(int& x, int& y) {
    cout << this->name << " (" << this->symbol << "), enter the current position (row column): ";
    cin >> x >> y;
    cout << "Enter the new position (row column): ";
    cin >> *ptr_new_x >> *ptr_new_y;
}

// Constructor for RandomFourByFourPlayer
template <typename T>
RandomFourByFourPlayer<T>::RandomFourByFourPlayer(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

// Get move for RandomFourByFourPlayer
template <typename T>
void RandomFourByFourPlayer<T>::getmove(int& x, int& y) {

    x = rand() % 4; // Randomly choose a row between 0 and 3
    y = rand() % 4;// Randomly choose a column between 0 and 3
    *ptr_new_x = rand() % 4; // Randomly choose a new row between 0 and 3
    *ptr_new_y = rand() % 4;// Randomly choose a new column between 0 and 3
}

#endif // FOURBYFOUR_TIC_TAC_TOE_H
