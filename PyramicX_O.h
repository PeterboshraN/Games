#ifndef PYRAMICX_O_H
#define PYRAMICX_O_H

#include "BoardGame_Classes.h"

template <typename T>
class pyramicBoard:public Board<T> {
public:
    pyramicBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class PyramicPlayer : public Player<T> {
public:
    PyramicPlayer(string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class PyramicRandomPlayer : public RandomPlayer<T>{
public:
    PyramicRandomPlayer (T symbol);
    void getmove(int &x, int &y) ;
};


template <typename T>
class PyramicAiPlayer : public Player<T> {
public:
    PyramicAiPlayer(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
pyramicBoard<T>::pyramicBoard() {
    this->rows = 3;  // Pyramid has 3 rows
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        int row_length = 2 * i + 1;
        this->board[i] = new T[row_length]();
    }
    this->n_moves = 0;  // Initialize move counter
}



template <typename T>
bool pyramicBoard<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < 2 * x + 1 && (this->board[x][y] == 0 || mark == 0)) {
        this->board[x][y] = mark == 0 ? 0 : toupper(mark);
        this->n_moves += (mark == 0) ? -1 : 1;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void pyramicBoard<T>::display_board() {
    cout << endl;
    int num_rows = 3;

    for (int i = 0; i < num_rows; ++i) {
        int num_cells = 2 * i + 1;
        int leading_spaces = num_rows - i - 1;

        // Print leading spaces
        for (int k = 0; k < leading_spaces; ++k) {
            cout << "         ";
        }

        // Print cells
        for (int j = 0; j < num_cells; ++j) {
            if (this->board[i][j] == 0) {
                cout << "| (" << i << ", " << j << ") ";
            } else {
                cout << "|   " << this->board[i][j] << "    ";
            }
        }

        cout << "|" << endl; // End row
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool pyramicBoard<T>::is_win() {
    auto match = [](T a, T b, T c) { return a != 0 && a == b && b == c; };

    // Check all possible winning conditions
    return match(this->board[1][0], this->board[1][1], this->board[1][2]) ||           // Middle row
           match(this->board[2][0], this->board[2][1], this->board[2][2]) ||           // Bottom row (left)
           match(this->board[2][2], this->board[2][3], this->board[2][4]) ||           // Bottom row (right)
           match(this->board[2][1], this->board[2][2], this->board[2][3]) ||           // Bottom row (right)
           match(this->board[0][0], this->board[1][1], this->board[2][2]) ||           // Left diagonal
           match(this->board[0][0], this->board[1][0], this->board[2][0]) ||           // Middle diagonal (left)
           match(this->board[0][0], this->board[1][2], this->board[2][4]);             // Middle diagonal (right)
}

// Return true if 9 moves are done and no winner
template <typename T>
bool pyramicBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool pyramicBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
PyramicPlayer<T>::PyramicPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void PyramicPlayer<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "\nEnter your move (row and column): ";
        cin >> x >> y;
        if (x >= 0 && x < 3 && y >= 0 && y < 2 * x + 1) break;
        cout << "Invalid move. Please try again.\n";
    }
}

// Constructor for X_O_Random_Player
template <typename T>
PyramicRandomPlayer<T>::PyramicRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void PyramicRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % (2 * x + 1);
}



#include <limits>
#include <algorithm> // For std::max and std::min
using namespace std;
// Constructor for the templated class
template <typename T>
PyramicAiPlayer<T>::PyramicAiPlayer(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void PyramicAiPlayer<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();

    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
template <typename T>
int PyramicAiPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2 * i + 1; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> PyramicAiPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2*i+1; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Winning move found
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2*i+1; ++j) {
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Block opponent's winning move
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2*i+1; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }


    return bestMove;
}



#endif //_3X3X_O_H

