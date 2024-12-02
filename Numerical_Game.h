#ifndef NUMERICAL_GAME_H
#define NUMERICAL_GAME_H
#include "BoardGame_Classes.h"
class NumericalBoard : public Board<int> {
private:
    vector<vector<int>> board;
    set<int> used_numbers;

public:
    NumericalBoard() {
        board.resize(3, vector<int>(3, 0));
    }

    void display_board() override {
        cout << "Numerical Tic-Tac-Toe Board (Sum = 15 to win):\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    bool update_board(int x, int y, int num) override {
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != 0 || used_numbers.count(num)) {
            return false;
        }
        board[x][y] = num;
        used_numbers.insert(num);
        return true;
    }

    bool game_is_over() override {
        return is_win(15) || is_draw();
    }

    bool is_win(int target_sum) override {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] + board[i][1] + board[i][2] == target_sum ||
                board[0][i] + board[1][i] + board[2][i] == target_sum) {
                return true;
            }
        }
        // Check diagonals
        return (board[0][0] + board[1][1] + board[2][2] == target_sum ||
                board[0][2] + board[1][1] + board[2][0] == target_sum);
    }

    bool is_draw() override {
        for (auto& row : board) {
            for (int cell : row) {
                if (cell == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

class HumanNumericalPlayer : public Player<int> {
private:
    set<int> available_numbers;

public:
    HumanNumericalPlayer(const string& name, int symbol) : Player<int>(name, symbol) {
        if (symbol == 1) { // Odd numbers for Player 1
            available_numbers = {1, 3, 5, 7, 9};
        } else { // Even numbers for Player 2
            available_numbers = {2, 4, 6, 8};
        }
    }

    void get_move(Board<int>* board, int& x, int& y, int& num) override {
        cout << name << ", your available numbers: ";
        for (int n : available_numbers) {
            cout << n << " ";
        }
        cout << "\nEnter your move (row column number): ";
        cin >> x >> y >> num;
        x--; y--; // Adjust to 0-indexing

        while (!is_number_valid(num)) {
            cout << "Invalid number! Choose from your available numbers: ";
            for (int n : available_numbers) {
                cout << n << " ";
            }
            cout << endl;
            cin >> num;
        }
    }

    void remove_number(int num) {
        available_numbers.erase(num);
    }

    bool is_number_valid(int num) {
        return available_numbers.count(num) > 0;
    }
};

class NumericalGameManager : public GameManager<int> {
public:
    NumericalGameManager(Board<int>* board, Player<int>* player1, Player<int>* player2)
            : GameManager<int>(board, player1, player2) {}

    void run() override {
        int x, y, num;
        board->display_board();
        int current_player = 0;

        while (!board->game_is_over()) {
            Player<int>* currentPlayer = players[current_player];
            auto* humanPlayer = dynamic_cast<HumanNumericalPlayer*>(currentPlayer);

            cout << currentPlayer->get_name() << "'s turn.\n";
            if (humanPlayer) {
                humanPlayer->get_move(board, x, y, num);
                while (!board->update_board(x, y, num)) {
                    cout << "Invalid move! Try again.\n";
                    humanPlayer->get_move(board, x, y, num);
                }
                humanPlayer->remove_number(num);
            }

            board->display_board();

            if (board->is_win(15)) {
                cout << currentPlayer->get_name() << " wins!\n";
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
