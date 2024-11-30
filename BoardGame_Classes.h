#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Board {
public:
    virtual void display_board() = 0;
    virtual bool update_board(Board* board, int x, int y, T symbol) = 0;
    virtual bool game_is_over() = 0;
    virtual ~Board() {}
};

template <typename T>
class Player {
protected:
    string name;
    T symbol;
public:
    Player(const string& name, T symbol) : name(name), symbol(symbol) {}
    virtual void get_move(Board<T>* board, int& x, int& y, T& symbol) = 0;
    T get_symbol() const { return symbol; }
    string get_name() const { return name; }
    virtual ~Player() {}
};

template <typename T>
class GameManager {
protected:
    Board<T>* board;
    Player<T>* players[2];

public:
    GameManager(Board<T>* board, Player<T>* player1, Player<T>* player2) {
        this->board = board;
        players[0] = player1;
        players[1] = player2;
    }

    virtual void run() = 0;
    virtual ~GameManager() {}
};

#endif
