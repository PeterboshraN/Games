
#ifndef WORDX_O_H
#define WORDX_O_H

#include "BoardGame_Classes.h"

template <typename T>
class WordBoard:public Board<T> {
public:
    WordBoard();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();


};

template <typename T>
class WordPlayer : public Player<T> {
public:
    WordPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class WordRandomPlayer : public RandomPlayer<T>{
public:
    WordRandomPlayer (T symbol);
    void getmove(int &x, int &y) ;
};


template <typename T>
class WordAiPlayer : public Player<T> {
public:
    WordAiPlayer(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};



//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;

// Constructor for X_O_Board
template <typename T>
WordBoard<T>::WordBoard() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool WordBoard<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void WordBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
// Returns true if there is any winner
set<string> dictionary;
void loadDictionary(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening dictionary file!" << endl;
        return;
    }
    string word;
    while (getline(inputFile, word)) {
        dictionary.insert(word);
    }
}

template <typename T>
bool WordBoard<T>::is_win() {
    ifstream inputFile("dic.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open dictionary file!" << endl;
        return false;
    }

    // Load all dictionary words into a set for quick lookup
    unordered_set<string> dictionary;
    string word;
    while (getline(inputFile, word)) {
        dictionary.insert(word);
    }
    inputFile.close();

    // Check all rows
    for (int i = 0; i < this->rows; ++i) {
        string rowWord = "";
        for (int j = 0; j < this->columns; ++j) {
            rowWord += this->board[i][j];
        }
        if (dictionary.find(rowWord) != dictionary.end()) {
            return true;
        }
    }

    // Check all columns
    for (int j = 0; j < this->columns; ++j) {
        string colWord = "";
        for (int i = 0; i < this->rows; ++i) {
            colWord += this->board[i][j];
        }
        if (dictionary.find(colWord) != dictionary.end()) {
            return true;
        }
    }

    // Check diagonals
    string diag1 = "", diag2 = "";
    for (int i = 0; i < this->rows; ++i) {
        diag1 += this->board[i][i];                   // Top-left to bottom-right
        diag2 += this->board[i][this->columns - i - 1]; // Top-right to bottom-left
    }
    if (dictionary.find(diag1) != dictionary.end() || dictionary.find(diag2) != dictionary.end()) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool WordBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WordBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
WordPlayer<T>::WordPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void WordPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) and a letter separated by spaces: ";
    cin >> x >> y >> this->symbol;
}

// Constructor for X_O_Random_Player
template <typename T>
WordRandomPlayer<T>::WordRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void WordRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int randomIndex = rand() % 26;
    this ->symbol = 'A' + randomIndex;
}




// Constructor for the templated class
template <typename T>
WordAiPlayer<T>::WordAiPlayer(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void WordAiPlayer<T>::getmove(int& x, int& y) {
    std::pair<std::pair<int, int>, T> bestMove = getBestMove();
    x = bestMove.first.first;
    y = bestMove.first.second;
    this -> symbol = bestMove.second;
}
// Minimax algorithm to evaluate the board
template <typename T>
int WordAiPlayer<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> WordAiPlayer<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<std::pair<int, int>, T> bestMove = {{-1, -1}, 'A'};

    int randomIndex = rand() % 26;
    T opponentSymbol = 'A' + randomIndex;;

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Winning move found
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Block opponent's winning move
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }


    return bestMove;
}




#endif

