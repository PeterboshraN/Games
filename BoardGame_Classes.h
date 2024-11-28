#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H
#include <bits/stdc++.h>
using namespace std;

class Board {
public:
    virtual void display_board() = 0;
    virtual bool game_is_over() = 0;
    virtual bool update_board(int x, int y, char symbol) = 0;
    virtual bool is_win(char symbol) = 0;
    virtual bool is_draw() = 0;
    virtual ~Board() = default;
};

class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol) : name(name), symbol(symbol) {}

    string get_name() { return name; }
    char get_symbol() { return symbol; }

    virtual void get_move(int& x, int& y) = 0;

    virtual ~Player() = default;
};

class HumanConnectPlayer : public Player {
public:
    HumanConnectPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void get_move(int& x, int& y) {
        cout << "please enter your move column as like => (1 1) or (2 2)\n";
        cout << name << ", enter your move (column): ";
        cin >> x >> y;
        x--;
        y--;
    }
};

class RandomConnectPlayer : public Player {
public:
    RandomConnectPlayer(const string& name, char symbol) : Player(name, symbol) {
        srand(static_cast<unsigned>(time(0)));
    }

    void get_move(int& x, int& y) {
        x = rand() % 6;
        y = rand() % 7;
        cout << name << " chooses row " << x + 1 << " and column " << y + 1 << endl;
    }
};

class GameManager {
protected:
    Board* board;
    Player* players[2];

public:
    GameManager(Board* board, Player* player1, Player* player2)
            : board(board) {
        players[0] = player1;
        players[1] = player2;
    }

    virtual void run() = 0;

    virtual ~GameManager() {
        delete board;
        delete players[0];
        delete players[1];
    }
};

#endif
