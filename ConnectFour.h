#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "BoardGame_Classes.h"

// Connect Four Board class
class ConnectFourBoard : public Board<char> {
public:
    vector<vector<char>> board;

    ConnectFourBoard() {
        board.resize(6, vector<char>(7, '.'));
    }

    void display_board() override {
        cout << "Connect Four Board:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "1 2 3 4 5 6 7\n";
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= 6 || y < 0 || y >= 7 || board[x][y] != '.') {
            return false;
        }
        board[x][y] = symbol;
        return true;
    }

    bool game_is_over() override {
        return is_win('X') || is_win('O') || is_draw();
    }

    bool is_win(char symbol) override {
        // Check rows, columns, and diagonals for a win condition
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i][j+1] == symbol &&
                    board[i][j+2] == symbol && board[i][j+3] == symbol) {
                    return true;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] == symbol && board[i+1][j] == symbol &&
                    board[i+2][j] == symbol && board[i+3][j] == symbol) {
                    return true;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i+1][j+1] == symbol &&
                    board[i+2][j+2] == symbol && board[i+3][j+3] == symbol) {
                    return true;
                }
            }
        }
        for (int i = 3; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i-1][j+1] == symbol &&
                    board[i-2][j+2] == symbol && board[i-3][j+3] == symbol) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() override {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == '.') return false;
            }
        }
        return true;
    }
};

// Human Connect Four Player class
class HumanConnectPlayer : public Player<char> {
public:
    HumanConnectPlayer(const string& name, char symbol) : Player<char>(name, symbol) {}

    void get_move(Board<char>* board, int& x, int& y, char& symbol) override {
        auto* connectBoard = dynamic_cast<ConnectFourBoard*>(board);
        if (!connectBoard) {
            throw runtime_error("Invalid board type for HumanConnectPlayer.");
        }

        cout << name << ", enter your move (column 1-7): ";
        cin >> y;
        y--;
        x = find_empty_row(connectBoard, y);

        while (x == -1) {
            cout << "Column is full. Try another column: ";
            cin >> y;
            y--;
            x = find_empty_row(connectBoard, y);
        }

        symbol = this->symbol;
    }

private:
    int find_empty_row(ConnectFourBoard* board, int col) {
        for (int i = 5; i >= 0; i--) {
            if (board->board[i][col] == '.') {
                return i;
            }
        }
        return -1;
    }
};

// Connect Four Manager class
class ConnectFourManager : public GameManager<char> {
public:
    ConnectFourManager(Board<char>* board, Player<char>* player1, Player<char>* player2)
            : GameManager<char>(board, player1, player2) {}

    void run() override {
        int x, y;
        char symbol;

        board->display_board();

        int current_player = 0;
        while (!board->game_is_over()) {
            players[current_player]->get_move(board, x, y, symbol);

            while (!board->update_board(x, y, symbol)) {
                cout << "Invalid move! Try again.\n";
                players[current_player]->get_move(board, x, y, symbol);
            }

            board->display_board();

            if (board->is_win(symbol)) {
                cout << players[current_player]->get_name() << " wins!\n";
                return;
            }

            if (board->is_draw()) {
                cout << "It's a draw!\n";
                return;
            }

            current_player = 1 - current_player;
        }
    }
};

#endif
