/* 
 * File:   Board.cpp
 * Author: Jason Nawrocki
 * 
 * Created on April 1, 2015, 1:37 PM
 */

#include "Board.h"
//This function reads a file of characters into a puzzle, a 2D array
Board::Board() {
    string fileName;
    ifstream boardStream;
    
    //read in the board file name
    do {
        cout << "Enter the board file name: ";
        cin >> fileName;
        boardStream.open(fileName.c_str(), ios::in);
    } while (!boardStream.good());     //continue until successful open
    
    string line;
    //Check that the file isn't empty
    if (!getline(boardStream, line)) {
        cerr << "Error: board file is empty" << endl;
        numRows = 0;
        numCols = 0;
        return;
    }
    
    // put the first board line in theBoard
    numCols = line.size();
    for (int i = 0; i < numCols; i++) {
        theBoard[0][i] = tolower(line.at(i));
    }
    
    //put the rest of the lines in theBoard
    for (numRows = 1; getline(boardStream, line); numRows++) {
        
        //make sure it's rectangular
        if (line.size() != numCols) {
            cerr << "Error: puzzle is not rectangular" << endl;
            numRows = 0;
            numCols = 0;
            return;
        }
        //put this board line in theBoard
        for (int i = 0; i < numCols; i++) {
            theBoard[numRows][i] = tolower(line.at(i));
        }
    }
    //wordsFound = NULL;
        
}
//This function prints the puzzle board in upper case letters
void Board::printBoard() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            cout << char(toupper(theBoard[r][c]));
        }
        cout << endl;
    }
    cout << endl;
}

//This function initiates the check if a given word is on the board
//it compares a word taken from input to new strings built on the board
//
//It is used in the human solving part
bool Board::checkBoard(string word) {
    string newWord;
    //check if the word was already entered
    if (binarySearchVector(word, 0, wordsFound.size() - 1, wordsFound) == true){
        cout << word << " already entered." << endl;
        return false;
    }
    char newBoard[MAX_ROWS][MAX_COLUMNS];
    //run through each position of the board
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            
            //make a new board, which will be changed, at each location
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++){
                    newBoard[i][j] = theBoard[i][j];
                }
            }
            //start building the new word from an empty string
            newWord = "";
            
            //see if the word is on the board, using findWord function
            bool check = findWord(newBoard, newWord, word, r, c);
            //if it is found, at it to wordsFound and sort wordsFound
            if (check == true) {
                wordsFound.push_back(word);
                sort(wordsFound.begin(), wordsFound.end());
                return check;
            }
            
        }
    }
            
}

//this function recursively checks strings on the board
//it tries to match them to an inputed word
//it takes as input the newBoard, the new string being build, and the r and c
//
//it is used in the human solving part
bool Board::findWord(char newBoard[MAX_ROWS][MAX_COLUMNS], string newWord, string word, int r, int c) {
    //continue building the string
    newWord = newWord + newBoard[r][c];
    //check for the case of "q"
    if (newBoard[r][c] == 'q') {
        newWord = newWord + 'u';
    }
    //check if the newWord is a substring of the word
    if (word.substr(0,newWord.length()) != newWord) {
        return false;
    }
    //make the current space a blank character. this elimintes backtracking
    newBoard[r][c] = ' ';
    //check that the location is legal and the word isn't too long
    if (r < 0 || r >= numRows || c < 0 || c >= numCols) {
        return false;
    }
    if (newWord.length() > word.length()) {
        return false;
    }
    //check if you have found the word on the board
    if (newWord == word) {
        return true;
    }
    bool check2;
    //recursive call for all 8 directions
    for (int dx = -1; dx < 2; dx++){
        for (int dy = -1; dy < 2; dy++) {
 
            //check for a valid direction
            if (dx == 0 && dy == 0) {
                continue;
            }
            //check that the new direction leads to a place on the board
            if (r + dx < 0 || r + dx >= numRows || c + dy < 0 || c + dy >= numCols) {
                continue;
            }
            //recursive call
            check2 = findWord(newBoard, newWord, word, r + dx, c + dy);
            if (check2 == true) {
                return true;
            }
            
        }
    }
    return check2;
}

//this function initiates the computer solving the entire board
int Board::solveBoard() {
    int score = 0;
    int count = 0;
    string newWord = "";
    char newBoard[MAX_ROWS][MAX_COLUMNS];
    
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            //create a new board which will be changed
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++){
                    newBoard[i][j] = theBoard[i][j];
                }
            }
            //call the checkAllWords function
            checkAllWords(newWord, newBoard, r, c, score, count);                
        }
    }
    //cout << "count is: " << count << endl;
    return score;
}

//This function finds all words on the board, by recursively building strings
//it takes as input the string being built, the new board to be changed,
//the row, the column, the score, and the count of words found
//It is used in the computer solving part
void Board::checkAllWords(string newWord, char newBoard[MAX_ROWS][MAX_COLUMNS], int r, int c, int &score, int &count) {
    
    char newArray[MAX_ROWS][MAX_COLUMNS];
    //build the string
    newWord = newWord + newBoard[r][c];
    //check for the q case
    if (newBoard[r][c] == 'q') {
        newWord = newWord + 'u';
    }
    //check that the new word is a prefix
    bool check = dictionary.isPrefix(newWord, 0, dictionary.size() -1);
    if (check == false) {
        return;
    }
    
    //build a new board, to be changed
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++){
            newArray[i][j] = newBoard[i][j];
        }
    }
    //avoid backtracking by changing the current space to a blank character
    newArray[r][c] = ' ';
    //check that the row and column are on the board
    if (r < 0 || r >= numRows || c < 0 || c >= numCols) {
        return;
    }
    //if the word is of valid length, search the dictionary for it
    if (newWord.length() >= 3) {
        bool check1 = dictionary.binarySearch(newWord, 0, dictionary.size() - 1);
        if (check1 == true) {
            //make sure the word hasn't already been found
            bool check2 = binarySearchVector(newWord, 0, wordsFound.size() - 1, wordsFound);
            if (check2 == false) {
                wordsFound.push_back(newWord);
                sort(wordsFound.begin(), wordsFound.end());
                score += wordScore(newWord); 
                count += 1;
            }
        }
    }    
    
    //for all 8 directions, recursively call the function and build strings
    for (int dx = -1; dx < 2; dx++){
        for (int dy = -1; dy < 2; dy++) {
 
            if (dx == 0 && dy == 0) {
                continue;
            }
            if (r + dx < 0 || r + dx >= numRows || c + dy < 0 || c + dy >= numCols) {
                continue;
            }
            checkAllWords(newWord, newArray, r + dx, c + dy, score, count);
        }
    }
    return;
    
    
}


//this function determines the score value of a word based on length
int Board::wordScore(string word) {
    int len = word.length();
    if (len == 3 || len == 4) {
        return 1;
    }
    if (len == 5) {
        return 2;
    }
    if (len == 6) {
        return 3;
    }
    if (len == 7) {
        return 5;
    }
    if (len > 7) {
        return 11;
    }
}
//This is an implementation of a recursive binarySearch
//It returns a bool value of true or false
bool Board::binarySearch(string word, int iMin, int iMax) {
    
    //test if vector is empty, if so, return false, it isn't in the dictionary
    int iMid;
    if (iMin > iMax) {
        return false;
    }
    //find the middle index of the dictionary
    else {
        iMid = (iMin + iMax)/2;
    }
    
    //comparisons. find which half the word would lie, then search that half
    if (dictionary.at(iMid) > word) {
        return binarySearch(word, iMin, iMid - 1);
    }
    if (dictionary.at(iMid) < word) {
        return binarySearch(word, iMid + 1, iMax);
    }
    //if we have found the word, return true
    if (dictionary.at(iMid) == word) {
        return true;
    }
    
}

//This is an implementation of a recursive binarySearch, usable with any vector
//It returns a bool value of true or false
bool Board::binarySearchVector(string word, int iMin, int iMax, vector <string> vect) {
    
    //test if vector is empty, if so, return false, it isn't in the dictionary
    int iMid;
    if (iMin > iMax) {
        return false;
    }
    //find the middle index of the dictionary
    else {
        iMid = (iMin + iMax)/2;
    }
    
    //comparisons. find which half the word would lie, then search that half
    if (vect.at(iMid) > word) {
        return binarySearchVector(word, iMin, iMid - 1, vect);
    }
    if (vect.at(iMid) < word) {
        return binarySearchVector(word, iMid + 1, iMax, vect);
    }
    //if we have found the word, return true
    if (vect.at(iMid) == word) {
        return true;
    }
    
}

//this function prints the wordsFound vector
void Board::printWordsFound() {
    for (vector <string>::iterator it = wordsFound.begin(); it != wordsFound.end(); ++it) {
        cout << ' ' << *it;
    }
    return;
}
