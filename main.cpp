#include "ConnectFour.h"
#include "Numerical_Game.h"
int main() {
//    auto* board = new ConnectFourBoard();
//    auto* player1 = new HumanConnectPlayer("Player 1", 'X');
//    auto* player2 = new HumanConnectPlayer("Player 2", 'O');
//    ConnectFourManager manager(board, player1, player2);
//    manager.run();
    NumericalBoard* board = new NumericalBoard();
    Player<int>* player1 = new HumanNumericalPlayer("Player 1", 1);
    Player<int>* player2 = new HumanNumericalPlayer("Player 2", 2);
    NumericalGameManager gameManager(board, player1, player2);
    gameManager.run();

    return 0;
}
