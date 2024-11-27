#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Abstract Board class
class Board {
public:
    virtual void display_board() = 0;
    virtual bool game_is_over() = 0;
    virtual bool update_board(int x, int y, char symbol) = 0;
    virtual bool is_win(char symbol) = 0;
    virtual bool is_draw() = 0;
    virtual ~Board() = default;
};

// Player class
class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol) : name(name), symbol(symbol) {}
    virtual void get_move(int& x, int& y) = 0;
    string get_name() const { return name; }
    char get_symbol() const { return symbol; }
    virtual ~Player() = default;
};

// Random Player class
class RandomPlayer : public Player {
public:
    RandomPlayer(const string& name, char symbol) : Player(name, symbol) {
        srand(time(0));
    }

    void get_move(int& x, int& y) {
        x = rand() % 3;
        y = rand() % 3;
    }
};

// Game Manager class
class GameManager {
private:
    Board* board;
    Player* players[2];

public:
    GameManager(Board* board, Player* player1, Player* player2)
            : board(board) {
        players[0] = player1;
        players[1] = player2;
    }

    void run() {
        int x, y;
        board->display_board();

        while (!board->game_is_over()) {
            for (int i = 0; i < 2; ++i) {
                Player* current_player = players[i];
                do {
                    current_player->get_move(x, y);
                } while (!board->update_board(x, y, current_player->get_symbol()));

                board->display_board();

                if (board->is_win(current_player->get_symbol())) {
                    cout << current_player->get_name() << " wins!" << endl;
                    return;
                }

                if (board->is_draw()) {
                    cout << "It's a draw!" << endl;
                    return;
                }
            }
        }
    }

    ~GameManager() {
        delete board;
        delete players[0];
        delete players[1];
    }
};

#endif
