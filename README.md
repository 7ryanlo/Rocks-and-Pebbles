# Rocks-and-Pebbles

Rocks and Pebbles is a variation of the popular codebreaking game, "Mastermind." Crack the code by trying to guess what the computer's secret word is in as few tries as possible. If guess is incorrect, computer will tell you how close you are by printing how many letters are correctly in the right position (rocks) and how many letters are correct but in the incorrect position (pebbles).

Coded in C++ and must be run in a console. Before playing, load words into the program by replacing the string in utilities.cpp file:
    
    const char WORDFILENAME[] = "/Users/Ryan/Documents/workspaceXCODE/CS 31 Projects/Project 5 Rocks/words.txt"; //line 27

to your destination of words.txt.
