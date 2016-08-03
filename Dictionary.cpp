/* 
 * File:   Dictionary.cpp
 * Author: Jason Nawrocki
 * 
 * Created on April 1, 2015, 1:33 PM
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
    //read file
    string fileName;
    ifstream dictionaryStream;
    
    //read in the dictionary file name
    do {
        cout << "Enter dictionary file name: ";
        cin >> fileName;
        dictionaryStream.open(fileName.c_str(), ios::in);
    } while (!dictionaryStream.good());
    
    string line;
    //make sure the file has something in it
    if (!getline(dictionaryStream, line)) {
        cerr << "Error: dictionary file is empty" << endl;
        return;
    }
    dictionary.push_back(line);
    
    
    //read words into the dictionary
    while (dictionaryStream >> line) {
        dictionary.push_back(line);
    }
    cout << "Dictionary size is " << dictionary.size() << endl << endl;
    
}
//This is an implementation of a recursive binarySearch
//It returns a bool value of true or false
bool Dictionary::binarySearch(string word, int iMin, int iMax) {
    
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

//this function works like binary search
//it searches the dictionary to see if a given string is a substring of a word
//it returns true or false, based on if the string was a substring or not
bool Dictionary::isPrefix(string word, int iMin, int iMax) {
    int iMid;
    //Check if the dictionary is empty. if so, return false, not a substring
    if (iMin > iMax) {
        return false;
    }
    //Find the middle index
    else {
        iMid = (iMin + iMax)/2;
    }
    
    //comparisons: check which half the string would be in
    if (dictionary.at(iMid).substr(0,word.length()) > word){
        return Dictionary::isPrefix( word, iMin, iMid - 1);
    }
    if (dictionary.at(iMid).substr(0,word.length()) < word) {
        return Dictionary::isPrefix(word, iMid + 1, iMax);
    }
    //if it is found to be a substring of a word, return truer
    if (dictionary.at(iMid).substr(0,word.length()) == word) {
        return true;
    }
}




