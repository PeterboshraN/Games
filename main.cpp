#include "ConnectFour.h"
#include "Numerical_Game.h"
#include "4x4_Tic_Tac_Toe.h"
int main() {

//    int choice;
//    Player<char> *players[2];
//    string playerXName, playerOName;
//    ConnectFourBoard<char> *B = new ConnectFourBoard<char>();  // Create the ConnectFour board
//
//    cout << "Welcome to ConnectFour Game.\n";
//    cout << "Enter Player (X) name: ";
//    cin >> playerXName;
//    cout << "Choose Player (X) type:\n";
//    cout << "1. Human\n";
//    cout << "2. Random Computer\n";
//    cin >> choice;
//    switch (choice) {
//        case 1:
//            players[0] = new HumanConnectPlayer<char>(playerXName, 'X');
//            break;
//        case 2:
//            players[0] = new RandomConnectPlayer<char>('X');
//            break;
//        default:
//            cout << "Invalid choice for Player (X). Exiting the game.\n";
//            return 1;
//    }
//
//    // Set up player 2
//    cout << "Enter Player (O) name: ";
//    cin >> playerOName;
//    cout << "Choose Player (O) type:\n";
//    cout << "1. Human\n";
//    cout << "2. Random Computer\n";
//    cin >> choice;
//
//    switch (choice) {
//        case 1:
//            players[1] = new HumanConnectPlayer<char>(playerOName, 'O');
//            break;
//        case 2:
//            players[1] = new RandomConnectPlayer<char>('O');
//            break;
//        default:
//            cout << "Invalid choice for Player (O). Exiting the game.\n";
//            return 1;
//    }
//
//    // Set the board for each player
//    for (int i = 0; i < 2; ++i) {
//        players[i]->setBoard(B);
//    }
//
//    // Run the game
//    GameManager<char> ConnectFour_Game(B, players);
//    ConnectFour_Game.run();
//
//    // Clean up memory
//    for (int i = 0; i < 2; ++i) {
//        delete players[i];  // Deallocate memory for players
//    }
//    delete B;
//
//    int choice;
//    Player<char>* players[2];
//    string player1Name, player2Name;
//    NumericalBoard<char>* B = new NumericalBoard<char>();
//
//    cout << "Welcome to Numerical Game.\n";
//      cout << "Rules: Player 1 typically starts and uses odd numbers\n"
//              "(1, 3, 5, 7, 9), while Player 2 uses even numbers (2, 4, 6, 8). Players alternate turns, placing one number in an\n"
//              "empty cell on the board. Each number can only be used once.\n";
//    cout << "Enter Player 1 name: ";
//    cin >> player1Name;
//    cout << "Choose Player 1 type:\n";
//    cout << "1. Human\n";
//    cout << "2. Random Computer\n";
//    cin >> choice;
//
//    switch (choice) {
//        case 1:
//            players[0] = new HumanNumericalPlayer<char>(player1Name, 'X');
//            break;
//        case 2:
//            players[0] = new RandomNumericalPlayer<char>( 'X');
//            break;
//        default:
//            cout << "Invalid choice for Player 1. Exiting the game.\n";
//            return 1;
//    }
//
//    cout << "Enter Player 2 name: ";
//    cin >> player2Name;
//    cout << "Choose Player 2 type:\n";
//    cout << "1. Human\n";
//    cout << "2. Random Computer\n";
//    cin >> choice;
//
//    switch (choice) {
//        case 1:
//            players[1] = new HumanNumericalPlayer<char>(player2Name, 'O');
//            break;
//        case 2:
//            players[1] = new RandomNumericalPlayer<char>('O');
//            break;
//        default:
//            cout << "Invalid choice for Player 2. Exiting the game.\n";
//            return 1;
//    }
//
//    GameManager<char> Numerical_Game(B, players);
//    Numerical_Game.run();
//
//    for (int i = 0; i < 2; ++i) {
//        delete players[i];  // Deallocate memory for players
//    }
//
    int choice;
    Player<char> *players[2];
    string playerXName, playerOName;
    FourByFourboard<char> *B = new  FourByFourboard<char>();

    cout << "Welcome to 4X4 Tic Tac Toe Game.\n";
    cout << "Rules: Players alternate turns, moving one of their tokens to\n"
            "an immediately adjacent open square. Tokens can be moved\n"
            "horizontally or vertically but not diagonally. Tokens may not jump over other tokens.\n";
    cout << "Enter Player (X) name: ";
    cin >> playerXName;
    cout << "Choose Player (X) type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    switch (choice) {
        case 1:
            players[0] = new FourByFourPlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new RandomFourByFourPlayer<char>(*B,'X');
            break;
        default:
            cout << "Invalid choice for Player (X). Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player (O) name: ";
    cin >> playerOName;
    cout << "Choose Player (O) type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new FourByFourPlayer<char>(playerOName, 'O');
            break;
        case 2:
            players[1] = new RandomFourByFourPlayer<char>(*B,'O');
            break;
        default:
            cout << "Invalid choice for Player (O). Exiting the game.\n";
            return 1;
    }

    // Set the board for each player
    for (int i = 0; i < 2; ++i) {
        players[i]->setBoard(B);
    }

    // Run the game
    GameManager<char> FourByFourGame(B, players);
    FourByFourGame.run();

    // Clean up memory
    for (int i = 0; i < 2; ++i) {
        delete players[i];  // Deallocate memory for players
    }
    delete B;
    return 0;
}
