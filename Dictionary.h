/* 
 * File:   Dictionary.h
 * Author: Jason Nawrocki
 *
 * Created on April 1, 2015, 1:33 PM
 */

#ifndef DICTIONARY_H
#define	DICTIONARY_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Dictionary {
public:
    Dictionary();
    bool binarySearch(string word, int iMin, int iMax);
    bool isPrefix(string word, int iMin, int iMax);
    int size() { return (int)dictionary.size();}
    string at(int i) { return dictionary.at(i);}
private:
    vector <string> dictionary;
};

#endif	/* DICTIONARY_H */

