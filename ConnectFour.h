#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class ConnectFourBoard : public Board<T> {
private:
    bool check_rows() {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (this->board[i][j] != T() &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2] &&
                    this->board[i][j] == this->board[i][j + 3]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool check_columns() {
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] != T() &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j] &&
                    this->board[i][j] == this->board[i + 3][j]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool check_diagonals() {
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (this->board[i][j] != T() &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2] &&
                    this->board[i][j] == this->board[i + 3][j + 3]) {
                    return true;
                }
            }
        }
        for (int i = 3; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (this->board[i][j] != T() &&
                    this->board[i][j] == this->board[i - 1][j + 1] &&
                    this->board[i][j] == this->board[i - 2][j + 2] &&
                    this->board[i][j] == this->board[i - 3][j + 3]) {
                    return true;
                }
            }
        }
        return false;
    }
    int find_empty_row(int col) {
        for (int i = this->rows - 1; i >= 0; --i) {
            if (this->board[i][col] == T()) {
                return i;
            }
        }
        return -1;
    }
    template <typename U>
    friend class ConnectFourMinMaxPlayer;
public:
    ConnectFourBoard() {
        this->rows = 6;
        this->columns = 7;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns]{};
        }
    }


    void display_board() override {
        cout << "Connect Four Board:\n";
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                cout << (this->board[i][j] == T() ? '.' : this->board[i][j]) << " ";
            }
            cout << endl;
        }
        cout << "1 2 3 4 5 6 7\n";
    }

    bool update_board(int x, int y, T symbol) override {
        if (y < 0 || y >= this->columns) return false;
        int empty_row = find_empty_row(y);
        if (empty_row == -1) return false;

        this->board[empty_row][y] = symbol;
        this->n_moves++;
        return true;
    }

    bool is_win() override {
        return check_rows() || check_columns() || check_diagonals();
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
    bool isValidMove(int col) {
        if (col < 0 || col >= this->columns) {
            cout << "Invalid column: " << col << endl;  // Debug output
            return false;
        }
        int empty_row = find_empty_row(col);
        if (empty_row == -1) {
            cout << "Column " << col << " is full." << endl;  // Debug output
            return false;
        }
        return true;
    }
    ~ConnectFourBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

};

template <typename T>
class HumanConnectPlayer : public Player<T> {
public:
    HumanConnectPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter your move (column 1-7): ";
        cin >> y;
        y--;
        while (y < 0 || y >= 7) {
            cout << "Invalid column. Enter a column (1-7): ";
            cin >> y;
            y--;
        }
        x = -1;
    }
};
template <typename T>
class RandomConnectPlayer : public RandomPlayer<T> {
public:
    RandomConnectPlayer(T symbol) : RandomPlayer<T>(symbol) {
        srand(static_cast<unsigned int>(time(nullptr))); // Seed for randomness
    }

    void getmove(int& x, int& y) override {
        // Randomly select a column (0-based indexing)
        y = rand() % 7; // Assuming the board has 7 columns
        x = -1;         // Row is not needed since Connect Four determines it automatically
    }
};

#endif
