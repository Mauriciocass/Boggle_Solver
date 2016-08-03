/* 
 * File:   main.cpp
 * Author: Jason Nawrocki
 *
 * This project simulates a boggle game
 * It allows the human player to decide if he/she would like to play against
 * the computer, or let the computer solve the board on its own
 * 
 * Created on April 1, 2015, 1:32 PM
 */

#include <cstdlib>
#include "Dictionary.h"
#include "Board.h"

using namespace std;

int main(int argc, char** argv) {
    
    Board boardObj = Board();
    boardObj.printBoard();
    
    //cin will store in x
    string x = "";
    while (x != "2" && x != "1") {
        cout << "Would you like to play or have the computer solve?" << endl;
        cout << "Enter 1 to play, enter 2 to let computer solve" << endl;
        cin >> x;
        if (x != "2" && x != "1") {
            cout << "Please enter a 1 or 2" << endl;
        }
    }
    
    int score = 0;
    int compScore = 0;
    string word;
    if (x == "1" ){
        cout << "You have chosen to play against the computer... good luck!";
        cout << endl << "Enter '!' if you give up:" << endl;
        while (word != "!") {
            cout << "enter a word: " << endl;
            cin >> word;
            if (word == "!") {         //check if the player wants to stop
                break;
            }
            //check that the word is long enough
            if (word.length() <3) {
                cout << "Word must be at least 3 letters long, try again" 
                        << endl;
                continue;
            }
            //check that the word is in the dictionary
            bool check = boardObj.binarySearch(word, 0, boardObj.size());
            if (check == false) {
                cout << "Must enter a word in the dictionary, try again"
                        << endl;
                continue;
            }
            //check that the word is on the board
            check = boardObj.checkBoard(word);
            if (check == false) {
                cout << "Must enter a new word on the board, try again"
                        << endl;
                continue;
            }
            //if the loop has not continued yet, the word is found
            cout << word << " found on the board!" << endl;
            score += boardObj.wordScore(word);
            cout << "Current score: " << score << endl << endl;
            boardObj.printBoard();
            cout << endl;
        }
        //now let the computer play
        cout << "thank you for playing!" << endl;
        cout << "you found these words: " << endl << "'";
        boardObj.printWordsFound();
        cout << "'" << endl << "you scored: " << score << endl;
        cout << "now let's see how the computer does!" << endl;
        compScore = boardObj.solveBoard();
        cout << "the computer scored: " << compScore << endl;
        cout << "the computer found these words: " << endl << "'";
        boardObj.printWordsFound();
        cout << "'";
    }
    else if (x == "2") {
        cout << "these words are on the board: " << endl;
        //let the computer solve the board
        int score = boardObj.solveBoard();
        boardObj.printWordsFound();
        cout << endl;
        cout << "maximum score is: " << score << endl;
    }
    
    return 0;
}

