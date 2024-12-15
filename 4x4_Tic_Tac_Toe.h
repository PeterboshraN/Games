#ifndef GAMES_4X4_TIC_TAC_TOE_H
#define GAMES_4X4_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class FourByFourboard : public Board<T> {
protected:
   vector<pair<int, int>> player1_tokens;
   vector<pair<int, int>> player2_tokens;
public:
    FourByFourboard() {
        this->rows = this->columns = 4;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '.';
            }
        }

        player1_tokens =  {{0, 1}, {0 , 3} , {3, 0} , {3 , 2}};
        player2_tokens = {{0, 0} ,{0 , 2}, {3 , 1} , {3 , 3}};
        for (auto& token : player1_tokens) {
            this->board[token.first][token.second] = 'X';
        }
        for (auto& token : player2_tokens) {
            this->board[token.first][token.second] = 'O';
        }

        this->n_moves = 0;
    }
    vector<pair<int , int>> getPlayer1_tokens(){
        return player1_tokens ;
    }
    vector<pair<int , int>> getPlayer2_tokens(){
        return player2_tokens ;
    }

    void display_board() override {
        cout << "\n4x4 Tic-Tac-Toe board:\n";
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool update_board(int x, int y, T symbol) override {
        int new_x, new_y;
        cout << "Enter the New position (New_row New_column): ";
        cin >> new_x >> new_y;

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != symbol) {
            cout << "Invalid move. The selected token doesn't match your symbol.\n";
            return false;
        }

        if (new_x < 0 || new_x >= this->rows || new_y < 0 || new_y >= this->columns || this->board[new_x][new_y] != '.') {
            cout << "Invalid move. The target cell is out of bounds or not empty.\n";
            return false;
        }

        int dx = abs(x - new_x);
        int dy = abs(y - new_y);
        if (dx + dy != 1) {
            cout << "Invalid move. You can only move one step in any direction.\n";
            return false;
        }

        this->board[x][y] = '.';
        this->board[new_x][new_y] = symbol;

        auto& tokens = (symbol == 'X') ? player1_tokens : player2_tokens;
        for (auto& token : tokens) {
            if (token.first == x && token.second == y) {
                token.first = new_x;
                token.second = new_y;
                break;
            }
        }

        ++this->n_moves;
        return true;
    }

    bool is_win() override {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] != '.') {
                    T current_symbol = this->board[i][j];

                    if (j + 2 < this->columns && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2]) {
                        return true;
                    }

                    if (i + 2 < this->rows && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j]) {
                        return true;
                    }

                    if (i + 2 < this->rows && j + 2 < this->columns && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2]) {
                        return true;
                    }

                    if (i - 2 >= 0 && j + 2 < this->columns && this->board[i][j] == this->board[i - 1][j + 1] && this->board[i][j] == this->board[i - 2][j + 2]) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
    ~FourByFourboard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
};

template <typename T>
class FourByFourPlayer : public Player<T> {
public:
    FourByFourPlayer(string n, T symbol) : Player<T>(n, symbol) {}

    void getmove(int& x, int& y) override {

        cout << this->name << " (" << this->symbol << "), Enter the current position of your token (Old_row Old_column): ";
        cin >> x >> y;
    }
};
template <typename T>
class RandomFourByFourPlayer : public RandomPlayer<T> {
private:
     FourByFourboard<T>& board;

public:
    RandomFourByFourPlayer(FourByFourboard<T>& boardRef, T symbol)
            : RandomPlayer<T>(symbol), board(boardRef) {
        srand(time(0));
    }

    void getmove(int& x, int& y) override {
        vector<pair<int, int>> tokens = (this->symbol == 'X') ? board.getPlayer1_tokens() : board.getPlayer2_tokens();
        auto token = tokens[rand() % tokens.size()];
        x = token.first;
        y = token.second;

        // Choose a random valid move
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        bool moved = false;
        for (int i = 0; i < 4; ++i) {
            int dir_idx = rand() % directions.size();
            int new_x = x + directions[dir_idx].first;
            int new_y = y + directions[dir_idx].second;
            if (new_x >= 0 && new_x < 4 && new_y >= 0 && new_y < 4 && board.board[new_x][new_y] == '.') {
                x = new_x;
                y = new_y;
                moved = true;
                break;
            }
        }
        if (!moved) {
            cout << "No valid moves available for " << this->name << ".\n";
        }
    }
};
#endif
