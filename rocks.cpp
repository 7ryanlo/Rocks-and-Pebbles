//
//  rocks.cpp
//  Project 5 Rocks
//
//  Created by Ryan on 11/9/15.
//  Copyright (c) 2015 Ryan. All rights reserved.
//

#include <stdio.h>
#include <cstring>
#include <iostream>
#include "utilities.h"
#include <algorithm>


using namespace std;

const int MAXWORDS = 9000;

int countRocks(char word[], char probe[]); //counts number of rocks

int countPebbles(char word[], char probe[]); //counts number of pebbles

int manageOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum); // plays one round of game

bool isLowerCaseChar(const char a[]); //check if cstring is a lowercase alphabet letter

bool isInWordsArray(const char probe[], int n, const char words[][MAXWORDLEN + 1]); //check if cstring is in the words array


void printArray(char words[][MAXWORDLEN +1], int n){
    for (int i = 0; i < n; i ++)
    {
        cerr << words[i] << " ";
    }
    cerr << endl;
}

int main() {
    
    char words[MAXWORDS][MAXWORDLEN + 1]; // sets cstring array of 9000 words each of length of at most 6 characters long and has the zerobyte
    
    int nWords = loadWords(words, 7265); // loads words into the cstring array "words"
    
    if (nWords < 1)
        cout << "No words were loaded, so I can't play the game." << endl; //if no words were loaded, do not play the game
    else
    {
        int numRounds;
        cout << "How many rounds do you want to play? ";
        cin >> numRounds; // get the number of rounds player wants to play
        
        if (numRounds < 1)
        {
            cout << "The number of rounds must be positive." << endl;
            return 0;
        }
        cin.ignore(1000, '\n');
        int totalTries = 0; // counter for the total number of tries player took in all rounds played
        
        int min = INT_MAX; //int to hold the lowest number of tries player took to finish a round. Preset to the biggest integer to compare to the number of rounds player took (most likely less)
        
        int max = 0; //int to hold the highest num of tries player took to finish a round. Preset to zero since it is impossible to guess in 0 rounds. Max number of tries will always be bigger than 0.
        
        for (int roundNum = 1; roundNum <= numRounds; roundNum ++)
        {
            cout << "\nRound " << roundNum << endl; // Display round number
            int wordnum = randInt(0, nWords - 1); //gets a random int between 0 and nWords - 1 to be the index of secret word
            
            cout << "The secret word is " << strlen(words[wordnum]) << " letters long."<< endl; // tells user how long secret word is
            
            
            int numTries = manageOneRound(words, nWords, wordnum); //plays a round of the game and determines number of tries taken to guess the word
            
            totalTries += numTries; //update the total number of tries
            
            if (numTries > 1)
                cout << "You got it in " << numTries << " tries." << endl; // display number of tries user took in plural form
            else
                cout << "You got it in 1 try." << endl; // tell user they guessed right in one try
            
            double average = static_cast<double>(totalTries) / roundNum; //calculate average tries
            
            if (numTries < min)
                min = numTries; // update min to the current lowest number of tries
            if (numTries > max)
                max = numTries; // update max to the current highest number of tries
            
            cout.setf(ios::fixed);//fixed point notation, not scientific
            cout.precision(2);    // causes digits after decimal to appear up to 2 digits to the right of decimal
            cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl;
            
        }
        
    }
}




//PLAYS ONE ROUND OF THE GAME
int manageOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
        return -1; // if number of words is not positive or the wordnum is outside of array boundaries, return -1
    
    char probe[100]; //character array for cstring containing user's guess
    
    
    int guesses = 0; // counter variable for the number of guesses player attempts
    
    char word[MAXWORDLEN + 1]; // declare cstring array containing the code word
    
    for (;;) //keep looping until break condition
    {
        strcpy(word, words[wordnum]); //store secret word into word c-string (restores the secret word upon another iteration of loop
        
        cout << "Probe = " << word << endl; //tester
        
        
        cout << "Probe word: "; //prompt user for probe word
        
        cin.getline(probe, 100); // read user input
        
        if (strlen(probe) < 4 || strlen(probe) > 6 || !isLowerCaseChar(probe))
        {   // if probe is not between 4 to 6 characters in length or is not a lowercase letter
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl; // tell user
            
            continue; // continue to next loop
        }
        
        if (!isInWordsArray(probe, nWords, words)) // if probe is not in the words array
        {
            cout << "I don't know that word." << endl; // tell user
            
            continue; //continue to next loop
        }
        
        guesses ++; //increment guesses counter
        
        if (strcmp(probe, words[wordnum]) == 0) //if the user found the word
            break; //break out of loop
        
        int rocks = countRocks(word, probe); //finds number of rocks
        
        int pebbles = countPebbles(word, probe); //finds number of pebbles
        
        cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl; //tells user how many rocks and pebbles found
        
    }
    
    
    return guesses;
}

int countRocks(char word[], char probe[]) //counts number of rocks
{
    int count = 0;
    for (int i = 0; probe[i] != '\0' ||  word[i] != '\0'; i ++) // loop until either cstring probe or word index is the zerobyte
    {
        if (probe[i] == word[i]) //update count if probe letter and word letter are same and at same index
        {
            count ++;
            probe[i] = '1'; // change element of probe to non alpha character
            word[i] = '1'; // change element of word to non alpha character
            //we change the probe and word elements so that we do not read any rocks as pebbles later on
        }
    }
    return count;
}

int countPebbles(char word[], char probe[]) //counts number of pebbles
{
    int count = 0;
    
    for (int i = 0; probe[i] != '\0'; i ++) // loop until probe index is the zerobyte
    {
        for (int j = 0; word[j] != '\0'; j ++) //loop until word index is the zerobyte
        {
            if (probe[i] == word[j] && i != j && isalpha(probe[i]) && isalpha(word[j]) ) // if the word and probe letter are same AND the indeces are not the same and both characters are alphabet chars
            {
                count ++; //increment count of pebbles by 1
                probe[i] = '1'; // change element of probe to non alpha character
                word[j] = '1'; // change element of word to non alpha character
                
            }
        }
    }
    return count;
}


bool isLowerCaseChar(const char a[]) //check if cstring is a lowercase alphabet letter
{
    for (int i = 0; a[i] != '\0'; i ++)// loop until zerobyte
        if (!islower(a[i]) || !isalpha(a[i])) //if character in cstring is not lowercase or not an letter
            return false; // return false
    
    return true; //return true otherwise
}

bool isInWordsArray(const char probe[], int n, const char words[][MAXWORDLEN + 1]) //check if cstring is in the words array
{
    for (int i = 0; i < n; i ++) // loop through the array
    {
        if (strcmp(words[i], probe) == 0) //return true if the probe word is in the words array
            return true;
    }
    return false;
}

