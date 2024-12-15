#ifndef NUMERICAL_GAME_H
#define NUMERICAL_GAME_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class NumericalBoard : public Board<T> {
public:
    NumericalBoard() {
        this->rows = 3;
        this->columns = 3;
        this->board = new T *[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new T[this->columns]();
        }
        this->n_moves = 0;
    }

    void display_board() override {
        cout << "\nNumerical Tic-Tac-Toe Board (Sum = 15 to win):\n";
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << (this->board[i][j] == 0 ? ". " : to_string(this->board[i][j]) + " ");
            }
            cout << endl;
        }
    }

    bool update_board(int x, int y, T num) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
            return false;
        }
        this->board[x][y] = num;
        this->n_moves++;
        return true;
    }

    bool is_win() override {
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] && this->board[i][1] && this->board[i][2] &&
                this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) {
                return true;
            }
            if (this->board[0][i] && this->board[1][i] && this->board[2][i] &&
                this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) {
                return true;
            }
        }
        return (this->board[0][0] && this->board[1][1] && this->board[2][2] &&
                this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
               (this->board[0][2] && this->board[1][1] && this->board[2][0] &&
                this->board[0][2] + this->board[1][1] + this->board[2][0] == 15);
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class HumanNumericalPlayer : public Player<T> {
private:
    set<T> available_numbers;
    int num;

    bool is_valid_move(int x, int y, int num) {
        return available_numbers.count(num) > 0 && x >= 0 && x < 3 && y >= 0 && y < 3;
    }

public:
    HumanNumericalPlayer(string name, T symbol) : Player<T>(name, symbol) {
        if (symbol == 'X') {
            available_numbers = {1, 3, 5, 7, 9};
        } else {
            available_numbers = {2, 4, 6, 8};
        }
    }

    void getmove(int &x, int &y) override {
        cout << this->name << ", available numbers: ";
        for (int n : available_numbers) {
            cout << n << " ";
        }
        cout << "\nEnter your move (row column number): ";
        cin >> x >> y >> num;

        // Ensure the move is valid.
        while (!is_valid_move(x, y, num)) {
            cout << "Invalid move! Try again: ";
            cin >> x >> y >> num;
        }

        this->symbol = num;
        available_numbers.erase(num);
    }
};

template <typename T>
class RandomNumericalPlayer : public RandomPlayer<T> {
private:
    vector<T> available_numbers;

public:
    RandomNumericalPlayer(T symbol) : RandomPlayer<T>(symbol) {
        if (symbol == 'X') {
            available_numbers = {1, 3, 5, 7, 9};
        } else {
            available_numbers = {2, 4, 6, 8};
        }
    }

    void getmove(int &x, int &y) override {
        srand(static_cast<unsigned int>(time(0)));
        x = rand() % 3;
        y = rand() % 3;

        if (!available_numbers.empty()) {
            int random_index = rand() % available_numbers.size();
            T random_num = available_numbers[random_index];

            this->symbol = random_num;

            available_numbers.erase(available_numbers.begin() + random_index);
        }
    }
};

#endif
