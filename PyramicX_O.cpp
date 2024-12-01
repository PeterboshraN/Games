#include "BoardGame_Classes.h"
#include "PyramicX_O.h"

template <typename T>
class PyramicBoard : public Board<T> {
private:
    vector<vector<T>> board;
    bool isWin = false;
    T empty_symbol;
public:
    PyramicBoard(T empty_symbol) : empty_symbol(empty_symbol) {
        board = {
                {empty_symbol},
                {empty_symbol, empty_symbol, empty_symbol},
                {empty_symbol, empty_symbol, empty_symbol, empty_symbol, empty_symbol}
        };
    }

    void display_board() override {
        int total_width = 9;
        int num_rows = 3;

        cout << "   ";
        for (int j = 0; j < total_width; ++j) {
            cout << (j + 1) % 10 << " ";
        }
        cout << endl;

        for (int i = 0; i < num_rows; ++i) {
            int num_cells = 2 * i + 1;
            int row_width = num_cells * 2 - 1;
            int leading_spaces = (total_width - row_width) / 2;

            cout << (i + 1) % 10 << " ";
            for (int k = 0; k < leading_spaces; ++k) {
                cout << " ";
            }
            for (int j = 0; j < num_cells; ++j) {
                cout << (board[i][j] == empty_symbol ? '.' : board[i][j]) << " ";
            }
            cout << endl;
        }
    }

    bool update_board(Board<T>* , int x, int y, T symbol) override {
        if (x < 0 || x >= 3 || y < 0 || y >= (2 * x + 1) || board[x][y] != empty_symbol) {
            return false;
        }
        board[x][y] = symbol;
        return true;
    }

    bool is_win(T symbol) {
        if (all_of(board[1].begin(), board[1].end(), [symbol](T c) { return c == symbol; })) return true;
        if (all_of(board[2].begin(), board[2].begin() + 3, [symbol](T c) { return c == symbol; })) return true;
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
        return false;
    }

    bool is_draw() {
        for (auto& row : board) {
            for (auto& cell : row) {
                if (cell == empty_symbol) return false;
            }
        }
        return true;
    }

    bool game_is_over() override {
        return is_win('X') || is_win('O') || is_draw();
    }
};


template <typename T>
class PyramicPlayer : public Player<T> {
public:
    PyramicPlayer(const string& name, T symbol)
            : Player<T>(name, symbol) {}

    void get_move(Board<T>* board, int& x, int& y, T& symbol) override {
        cout << this->name << ", enter your move (row, column): ";
        cin >> x >> y;
        x--;
        y--;

        if (!board->update_board(nullptr, x, y, this->symbol)) {
            cout << "Invalid move. Try again.\n";
            get_move(board, x, y, symbol);
            return;
        }
        symbol = this->symbol;
    }
};

template <typename T>

class RandomPlayer : public Player<T> {
public:
    RandomPlayer(const string& name, T symbol) : Player<T>(name, symbol) {
        srand(time(0));
    }

    void get_move(Board<T>* board, int& x, int& y, T& symbol) override {
        do {
            x = rand() % 3;
            y = rand() % (2 * x + 1); // Ensure y is within the valid range for the given x
        } while (!board->update_board(board, x, y, symbol));

        symbol = this->symbol;
    }

};


template <typename T>
class PyramicGameManager : public GameManager<T> {
public:
    PyramicGameManager(Board<T>* board, Player<T>* player1, Player<T>* player2)
            : GameManager<T>(board, player1, player2) {}

    void run() override {
        int x, y;
        T symbol;
        this->board->display_board();

        int current_player = 0;
        while (!this->board->game_is_over()) {
            Player<T>* currentPlayer = this->players[current_player];
            currentPlayer->get_move(this->board, x, y, symbol);

            while (!this->board->update_board(nullptr, x, y, symbol)) {
                cout << "Invalid move! Try again.\n";
                currentPlayer->get_move(this->board, x, y, symbol);
            }

            this->board->display_board();
            if (this->board->game_is_over()) {
                cout << currentPlayer->get_name() << " wins!" << endl;
                return;
            }
            current_player = 1 - current_player;
        }
    }
};
