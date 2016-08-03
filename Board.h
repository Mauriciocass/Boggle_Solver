/* 
 * File:   Board.h
 * Author: Jason Nawrocki
 * This class contains the methods and instance variables of the board
 * It provides the functionality needed to check words on the board
 * and solve the board
 * Created on April 1, 2015, 1:37 PM
 */

#ifndef BOARD_H
#define	BOARD_H

#define MAX_ROWS 100
#define MAX_COLUMNS 100
#define NUM_DIRECTIONS 8

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"

using namespace std;

class Board {
public:
    Board();
    void simpleSolve();
    void binarySolve();
    void prefixSolve();
    void printBoard();
    int getRows() {return numRows;}
    int getCols() {return numCols;}
    bool checkBoard(string word);
    bool findWord(char newBoard[MAX_ROWS][MAX_COLUMNS], string newWord,
        string word, int r, int c);
    bool binarySearch(string word, int iMin, int iMax);
    int size() { return (int)dictionary.size();}
    int wordScore(string word);
    int solveBoard();
    void checkAllWords(string newWord, char newBoard[MAX_ROWS][MAX_COLUMNS],
        int r, int c, int &score, int &count);
    bool binarySearchVector(string word, int iMin, int iMax,
        vector <string> vect);
    void printWordsFound();
    
private:
    char theBoard[MAX_ROWS][MAX_COLUMNS];
    vector <string> wordsFound;
    int numRows;
    int numCols;
    int minWordLength;
    Dictionary dictionary;
};

#endif	/* BOARD_H */

