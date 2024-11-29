#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "BoardGame_Classes.h"

class ConnectFourBoard : public Board {
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
        cout << "1 2 3 4 5 6 7 \n";
    }

    bool update_board(Board* board, int x, int y, int num) override {
        auto* connectBoard = dynamic_cast<ConnectFourBoard*>(board);
        if (!connectBoard) return false;

        if (x < 0 || x >= 6 || y < 0 || y >= 7 || connectBoard->board[x][y] != '.') {
            return false;
        }
        connectBoard->board[x][y] = (num == 1) ? 'X' : 'O';
        return true;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    bool is_win() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != '.' && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3]) {
                    return true;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] != '.' && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j] && board[i][j] == board[i+3][j]) {
                    return true;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != '.' && board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2] && board[i][j] == board[i+3][j+3]) {
                    return true;
                }
            }
        }
        for (int i = 3; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != '.' && board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2] && board[i][j] == board[i-3][j+3]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw() const {
        for (auto& row : board) {
            for (char cell : row) {
                if (cell == '.') return false;
            }
        }
        return true;
    }
};

class HumanConnectPlayer : public Player {
public:
    HumanConnectPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void get_move(Board* board, int& x, int& y, int& num) override {
        cout << name << ", enter your move (column): ";
        cin >> y;
        y--;
        x = find_empty_row(board, y);
        if (x == -1) {
            cout << "Column is full. Try again.\n";
            get_move(board, x, y, num);
        }

        num = (symbol == 'X') ? 1 : 2;
    }

    int find_empty_row(Board* board, int col) {
        auto* connectBoard = dynamic_cast<ConnectFourBoard*>(board);
        if (!connectBoard) return -1;

        for (int i = 5; i >= 0; i--) {
            if (connectBoard->board[i][col] == '.') {
                return i;
            }
        }
        return -1;
    }

};

class RandomConnectPlayer : public HumanConnectPlayer {
public:
    RandomConnectPlayer(const string& name, char symbol)
            : HumanConnectPlayer(name, symbol) {
        srand(static_cast<unsigned>(time(0)));
    }

    void get_move(Board* board, int& x, int& y, int& num) override {
        auto* connectBoard = dynamic_cast<ConnectFourBoard*>(board);
        if (!connectBoard) throw runtime_error("Invalid board type for RandomConnectPlayer");

        do {
            y = rand() % 7;
            x = find_empty_row(board, y);
        } while (x == -1);

        num = (symbol == 'X') ? 1 : 2;
        cout << name << " chooses column " << y + 1 << endl;
    }
};

class ConnectFourManager : public GameManager {
public:
    ConnectFourManager(Board* board, Player* player1, Player* player2)
            : GameManager(board, player1, player2) {}
    void run() override {
        int x, y, num;
        board->display_board();

        int current_player = 0;
        while (!board->game_is_over()) {
            Player* currentPlayer = players[current_player];
            currentPlayer->get_move(board, x, y, num);

            while (!board->update_board(board, x, y, num)) {
                cout << "Invalid move! Try again.\n";
                currentPlayer->get_move(board, x, y, num);
            }

            board->display_board();

            if (board->game_is_over()) {
                cout << currentPlayer->get_name() << " wins!" << endl;
                return;
            }
            current_player = 1 - current_player;
        }
    }
};

#endif
