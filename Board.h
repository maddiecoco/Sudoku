// Project 4 - Sudoku (EECE2560)
// Part a
// Collaborators: Madeline Coco, Neha Joby
// This file contains the definitions for the board class

#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

using namespace std;

class Board 
{
    public:
    //Default constructor, initialize board
    Board();
    // prints the board and conflict vectors to the screen
    void printBoard();
    // add a value to a cell, update conflict vectors
    void addValue();

    private:
    vector<vector<int>> _board;
    vector<vector<bool>> rowConflicts;
    vector<vector<bool>> colConflicts;
    vector<vector<bool>> squareConflicts;
};

#endif
