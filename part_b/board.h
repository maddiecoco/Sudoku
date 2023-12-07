// Maddie & Neha
// Sudoku Puzzle Part B


#ifndef BOARD_H
#define BOARD_H

// Standard libraries and header files used.
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;    // Makes standard library names available.

typedef int ValueType; // The type of the value in a cell
const int blank = -1;  // Indicates that a cell is blank

// Constants that define dimensions and value limits for the board.
const int squareSize = 3;   //  The number of cells in a small square
                            //  (usually 3).  The board has
                            //  SquareSize^2 rows and SquareSize^2
                            //  columns.
const int boardSize = squareSize * squareSize;
const int minValue = 1;
const int maxValue = 9;


// Board class declaration - Stores the entire Sudoku board.
class Board
{
public:
    Board(int sqSize);                 // Constructor - Initializes a Sudoku board of given size.
    void Clear();                      // Clears the board
    void Initialize(ifstream &fin);    // Initalizes the board with ifstream
    bool IsSolved();                   // Returns if the board is solved
    void Print();                      // Prints out the board
    void PrintConflicts();             // Prints out the conflicts

    bool IsBlank(int i, int j);                    // Returns if cell is blank
    ValueType GetCell(int i, int j);               // Returns value of cell
    void SetCell(int i, int j, ValueType val);     // Sets the cell to val
    void ClearCell(int i, int j);                  // Clears the cell

    bool CausesConflict(int i, int j, ValueType val);  // Would it cause conflict
    void AddConflict(int i, int j, ValueType val);     // Add a conflict
    void RemoveConflict(int i, int j, ValueType val);  // Remove conflict

    // Part B additions - Sudoku solving methods
    bool isLegal(int, int, int);    // Checks if a move is legal
    bool nextCell(int &, int &);    // Finds the next cell to be filled
    bool solve(int &count);         // Solves the Sudoku puzzle recursively
    int getRecursions();            // Returns the number of recursive calls made
    int recursions;                 // An integer variable to track recursion count

private:
// The following matrices go from 1 to BoardSize in each dimension.
// they are each (BoardSize+1) X (BoardSize+1)
    matrix<ValueType> value;        // Matrix to store cell values
    
    // Track conflicts in rows, columns, and squares
    matrix<bool> rowConflicts;
    matrix<bool> colConflicts;
    matrix<bool> sqConflicts;
    
    matrix<vector<bool>> placed;    // Tracks digits that have been placed on the board
};


#endif //BOARD_H
