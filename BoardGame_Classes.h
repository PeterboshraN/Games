#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H
#include <bits/stdc++.h>
using namespace std;
class Board {
public:
    virtual void display_board() = 0;
    virtual bool update_board(Board* board, int x, int y, int num) = 0;
    virtual bool game_is_over() = 0;
    virtual ~Board() {}
};

class Player {
protected:
    string name;
    char symbol;
public:
    Player(const string& name, char symbol) : name(name), symbol(symbol) {}
    virtual void get_move(class Board* board, int& x, int& y, int& num) = 0;
    char get_symbol() const { return symbol; }
    string get_name() const { return name; }
    virtual ~Player() {}
};

class GameManager {
protected:
    Board* board;
    Player* players[2];

public:
    GameManager(Board* board, Player* player1, Player* player2) {
        this->board = board;
        players[0] = player1;
        players[1] = player2;
    }

    virtual void run() = 0;
    virtual ~GameManager() {}
};
#endif
