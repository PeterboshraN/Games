#include <iostream>
#include "BoardGame_Classes.h"
#include "PyramicX_O.h"
#include "WordX_O.h"
#include "UltimateX_O.h"

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
        cout << "3. Ultimate Tic-tac-toe\n"; // Added option for Ultimate Tic-tac-toe
        cout << "4. Exit\n";
        cout << "Your choice: ";
        cin >> GameChoice;

        if (GameChoice == 4) {
            cout << "Thank you for playing! Goodbye!\n";
            exitGame = true;
            break;
        }

        if (GameChoice == 1) {
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
            cout << "Enter Player 2 name: ";
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
            continue;
        }

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

        // Ask if the user wants to play again
        int playAgain;
        cout << "\nWould you like to play another game? \n";
        cout << "1. Yes\n2. No\nYour choice: ";
        cin >> playAgain;
        if (playAgain != 1) {
            exitGame = true;
            cout << "Thank you for playing! Goodbye!\n";
        }
    }

    return 0;
}
