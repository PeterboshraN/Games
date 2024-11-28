#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include "BoardGame_Classes.h"

class ConnectFourBoard : public Board {
private:
    char board[6][7];

public:
    ConnectFourBoard() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void display_board() override {
        cout << "Connect Four Board:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                cout << (board[i][j] == ' ' ? '.' : board[i][j]) << " ";
            }
            cout << endl;
        }
        cout << "1 2 3 4 5 6 7" << endl;
    }

    bool update_board(int x, int y, char symbol) override {
        if (y < 0 || y >= 7) return false;
        for (int i = 5; i >= 0; i--) {
            if (board[i][y] == ' ') {
                board[i][y] = symbol;
                return true;
            }
        }
        return false;
    }

    bool game_is_over() override {
        return is_win('X') || is_win('O') || is_draw();
    }

    bool is_win(char symbol) override {
        // Horizontal check
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i][j + 1] == symbol &&
                    board[i][j + 2] == symbol && board[i][j + 3] == symbol) {
                    return true;
                }
            }
        }

        // Vertical check
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] == symbol && board[i + 1][j] == symbol &&
                    board[i + 2][j] == symbol && board[i + 3][j] == symbol) {
                    return true;
                }
            }
        }

        // Diagonal check (bottom-left to top-right)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol &&
                    board[i + 2][j + 2] == symbol && board[i + 3][j + 3] == symbol) {
                    return true;
                }
            }
        }

        // Diagonal check (top-left to bottom-right)
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 7; j++) {
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol &&
                    board[i + 2][j - 2] == symbol && board[i + 3][j - 3] == symbol) {
                    return true;
                }
            }
        }

        return false;
    }

    bool is_draw() override {
        for (int j = 0; j < 7; j++) {
            if (board[0][j] == ' ') {
                return false;
            }
        }
        return true;
    }
};

class ConnectFourManager : public GameManager {
public:
    ConnectFourManager(Board* board, Player* player1, Player* player2)
            : GameManager(board, player1, player2) {}

    void run() override {
        int x = 0, y;
        board->display_board();

        int current_player = 0;
        while (!board->game_is_over()) {
            Player* currentPlayer = players[current_player];
            currentPlayer->get_move(x, y);
            while (!board->update_board(x, y, currentPlayer->get_symbol())) {
                cout << "Invalid move! Try again.\n";
                currentPlayer->get_move(x, y);
            }

            board->display_board();

            if (board->is_win(currentPlayer->get_symbol())) {
                cout << currentPlayer->get_name() << " wins!" << endl;
                return;
            }

            if (board->is_draw()) {
                cout << "It's a draw!" << endl;
                return;
            }

            current_player = 1 - current_player;
        }
    }
};

#endif
