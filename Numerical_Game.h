#ifndef NUMERICAL_GAME_H
#define NUMERICAL_GAME_H

#include "BoardGame_Classes.h"

class NumericalBoard : public Board {
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
                if (board[i][j] == 0) cout << ". ";
                else cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    int get_cell(int x, int y) {
        return board[x][y];
    }
    bool update_board(Board* board, int x, int y, int num) override {
        // Assuming the current board is a NumericalBoard
        auto* numBoard = dynamic_cast<NumericalBoard*>(board);
        if (!numBoard) return false;

        if (x < 0 || x >= 3 || y < 0 || y >= 3 || numBoard->get_cell(x, y) != 0 || used_numbers.count(num) > 0) {
            return false;
        }
        numBoard->board[x][y] = num;
        used_numbers.insert(num);
        return true;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    bool is_win() {
        int target_sum = 15;
        for (int i = 0; i < 3; i++) {
            if (board[i][0] + board[i][1] + board[i][2] == target_sum) return true;
            if (board[0][i] + board[1][i] + board[2][i] == target_sum) return true;
        }
        if (board[0][0] + board[1][1] + board[2][2] == target_sum) return true;
        if (board[0][2] + board[1][1] + board[2][0] == target_sum) return true;
        return false;
    }

    bool is_draw() const {
        for (const auto& row : board) {
            for (int cell : row) {
                if (cell == 0) return false;
            }
        }
        return true;
    }
};

class HumanNumericalPlayer : public Player {
protected:
    set<int> available_numbers;

public:
    HumanNumericalPlayer(const string& name, char symbol) : Player(name, symbol) {
        if (symbol == 'X') {
            available_numbers = {1, 3, 5, 7, 9};
        } else {
            available_numbers = {2, 4, 6, 8};
        }
    }

    void get_move(Board* board, int& x, int& y, int& num) override {
        cout << "Available numbers: ";
        for (int available_num : available_numbers) {
            cout << available_num << " ";
        }
        cout << endl;

        cout << name << ", enter your move (row column number): ";
        cin >> x >> y >> num;
        x--; y--;
        if (is_number_valid(num)) {
            remove_number(num);
        } else {
            cout << "Invalid number. Please choose another number from the available ones." << endl;
            get_move(board, x, y, num);
        }
    }

    bool is_number_valid(int num) {
        return available_numbers.count(num) > 0;
    }

    void remove_number(int num) {
        available_numbers.erase(num);
    }
};

class RandomNumericalPlayer : public HumanNumericalPlayer {
public:
    RandomNumericalPlayer(const string& name, char symbol)
            : HumanNumericalPlayer(name, symbol) {
        srand(static_cast<unsigned>(time(0)));
    }

    void get_move(Board* board, int& x, int& y, int& num) override {
        auto* numBoard = dynamic_cast<NumericalBoard*>(board);
        if (!numBoard) throw runtime_error("Invalid board type for RandomNumericalPlayer");

        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (numBoard->get_cell(x, y) != 0);

        num = *available_numbers.begin();
        available_numbers.erase(num);
        cout << name << " chooses row " << x + 1 << " and column " << y + 1 << " with number " << num << endl;
    }
};

class NumericalGameManager : public GameManager {
public:
    NumericalGameManager(Board* board, Player* player1, Player* player2)
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
