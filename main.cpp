#include <iostream>
#include "BoardGame_Classes.h"
#include "PyramicX_O.h"
#include "WordX_O.h"
#include "UltimateX_O.h"
#include "FourByFour_Tic_Tac_Toe.h" 
#include "ConnectFour.h" 
#include "Numerical_Game.h" 

using namespace std;

int main() {
    int choice, GameChoice;
    bool exitGame = false;

    while (!exitGame) {
        Player<char>* players[2] = {nullptr, nullptr};
        Board<char>* B = nullptr;

        cout << "\n*** Welcome to Tic-tac-toe Games ***\n";
        cout << "Choose a game:\n";
        cout << "1. Pyramic Tic-tac-toe\n";
        cout << "2. Word Tic-tac-toe\n";
        cout << "3. Ultimate Tic-tac-toe\n";
        cout << "4. 4x4 Tic-tac-toe\n";
        cout << "5. Connect Four\n"; 
        cout << "6. Numerical Tic-tac-toe\n";
        cout << "7. Exit\n";
        cout << "Your choice: ";
        cin >> GameChoice;

        if (GameChoice == 7) {
            cout << "Thank you for playing! Goodbye!\n";
            exitGame = true;
            break;
        }

        if (GameChoice == 6) {
            B = new NumericalBoard<char>();
            cout << "\n*** Numerical Tic-tac-toe ***\n";

            // Set up Player 1
            string player1Name;
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new HumanNumericalPlayer<char>(player1Name, 'X');
                    break;
                case 2:
                    players[0] = new RandomNumericalPlayer<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Restarting the menu...\n";
                    delete B;
                    continue;
            }

            // Set up Player 2
            string player2Name;
            cout << "\nEnter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new HumanNumericalPlayer<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new RandomNumericalPlayer<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Restarting the menu...\n";
                    delete B;
                    delete players[0];
                    continue;
            }

            GameManager<char> NumericalGame(B, players);
            NumericalGame.run();
        }

        if (GameChoice == 5) {
            B = new ConnectFourBoard<char>();
            cout << "\n*** Connect Four ***\n";

            // Set up Player 1
            string playerXName;
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new HumanConnectPlayer<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new RandomConnectPlayer<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player X. Restarting the menu...\n";
                    delete B;
                    continue;
            }

            // Set up Player 2
            string player2Name;
            cout << "\nEnter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new HumanConnectPlayer<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new RandomConnectPlayer<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Restarting the menu...\n";
                    delete B;
                    delete players[0];
                    continue;
            }

            GameManager<char> ConnectFourGame(B, players);
            ConnectFourGame.run();
        } else if (GameChoice == 4) {
            B = new FourByFourBoard<char>();
            cout << "\n*** 4x4 Tic-tac-toe ***\n";

            // Set up Player 1
            string playerXName;
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new FourByFourPlayer<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new RandomFourByFourPlayer<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player X. Restarting the menu...\n";
                    delete B;
                    continue;
            }

            // Set up Player 2
            string player2Name;
            cout << "\nEnter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new FourByFourPlayer<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new RandomFourByFourPlayer<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Restarting the menu...\n";
                    delete B;
                    delete players[0];
                    continue;
            }

            GameManager<char> FourByFourGame(B, players);
            FourByFourGame.run();
        } else if (GameChoice == 1) {
            B = new pyramicBoard<char>();
            cout << "\n*** Pyramic Tic-tac-toe ***\n";

            // Set up Player 1
            string playerXName;
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new PyramicPlayer<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new PyramicRandomPlayer<char>('X');
                    break;
                case 3:
                    players[0] = new PyramicAiPlayer<char>('X');
                    players[0]->setBoard(B);
                    break;
                default:
                    cout << "Invalid choice for Player X. Restarting the menu...\n";
                    delete B;
                    continue;
            }

            // Set up Player 2
            string player2Name;
            cout << "\nEnter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new PyramicPlayer<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new PyramicRandomPlayer<char>('O');
                    break;
                case 3:
                    players[1] = new PyramicAiPlayer<char>('O');
                    players[1]->setBoard(B);
                    break;
                default:
                    cout << "Invalid choice for Player 2. Restarting the menu...\n";
                    delete B;
                    delete players[0];
                    continue;
            }

            GameManager<char> pyramicGame(B, players);
            pyramicGame.run();
        } else if (GameChoice == 2) {
            char letter = ' ';
            B = new WordBoard<char>();
            cout << "\n*** Word Tic-tac-toe ***\n";

            // Set up Player 1
            string playerXName;
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new WordPlayer<char>(playerXName, letter);
                    break;
                case 2:
                    players[0] = new WordRandomPlayer<char>(letter);
                    break;
                default:
                    cout << "Invalid choice for Player X. Restarting the menu...\n";
                    delete B;
                    continue;
            }

            // Set up Player 2
            string player2Name;
            cout << "\nEnter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new WordPlayer<char>(player2Name, letter);
                    break;
                case 2:
                    players[1] = new WordRandomPlayer<char>(letter);
                    break;
                default:
                    cout << "Invalid choice for Player 2. Restarting the menu...\n";
                    delete B;
                    delete players[0];
                    continue;
            }

            GameManager<char> WordGame(B, players);
            WordGame.run();
        } else if (GameChoice == 3) {
            B = new UltimateBoard<char>();
            cout << "\n*** Ultimate Tic-tac-toe ***\n";

            // Set up Player 1
            string playerXName;
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new UltimatePlayer<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new UltimateRandomPlayer<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player X. Restarting the menu...\n";
                    delete B;
                    continue;
            }

            // Set up Player 2
            string player2Name;
            cout << "\nEnter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new UltimatePlayer<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new UltimateRandomPlayer<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Restarting the menu...\n";
                    delete B;
                    delete players[0];
                    continue;
            }

            GameManager<char> UltimateGame(B, players);
            UltimateGame.run();
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

        // Cleanup
        delete players[0];
        delete players[1];
        delete B;
    }

    return 0;
}
