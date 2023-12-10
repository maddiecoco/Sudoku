// Maddie & Neha
// Sudoku Puzzle Part B


// Declarations and functions
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "board.h"

using namespace std;

// Board constructor - Initializes matrices for the Sudoku board values and conflict 
// tracking for rows, columns, and squares.
Board::Board(int sqSize)
        : value(boardSize + 1, boardSize + 1),
          rowConflicts(boardSize + 1, boardSize + 1),
          colConflicts(boardSize + 1, boardSize + 1),
          sqConflicts(boardSize + 1, boardSize + 1) {
}


// Clear function - Resets all cells on the board.
void Board::Clear() {
    //For each element in the value matrix, clear the cell
    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            ClearCell(i, j);
        }
    }
}


// Initialize funciton - Reads a Sudoku board from the input file, setting
// values for non-empty cells.
void Board::Initialize(ifstream &fin) {
    char ch;

    Clear(); // Make sure board is empty
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++) {
            fin >> ch;

            // If the read char is not blank
            if (ch != '.') {
                int val = ch - '0'; //Convert char to int
                SetCell(i, j, val); //Set cell to value
            } else {
                SetCell(i, j, blank); //Set cell to blank
            }
        }
}


// SquareNumber function - Calculates the square number of a cell based on
// its row and column.
int SquareNumber(int i, int j) {
//Return the square number of cell i,j (counting from left to right,
//top to bottom.  Note that i and j each go from 1 to BoardSize)

    //Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    //coordinates of the square that i,j is in.

    return squareSize * ((i - 1) / squareSize) + (j - 1) / squareSize + 1;
}


// Overloaded Operator - Enables easy printing of vectors, particularly useful
// for debugging.
ostream &operator<<(ostream &ostr, vector<int> &v) {
//Overloaded output operator for vector class.
    for (int i = 0; i < (int)v.size(); i++)
        ostr << v[i] << " ";
    ostr << endl;
    return ostr;
}


// GetCell & IsBlank functions - Retrieve cell values and check if a cell is
// blank, with error checking.

// Returns the value stored in a cell.  Throws an exception if bad values are passed.
ValueType Board::GetCell(int i, int j) {
    if (i >= 1 && i <= boardSize && j >= 1 && j <= boardSize)
        return value[i][j];
    else
        throw rangeError("Bad value in GetCell");
}

// Returns true if cell i,j is blank, and false otherwise.
bool Board::IsBlank(int i, int j) {
    // Throw error if out of board range
    if (i < 1 || i > boardSize || j < 1 || j > boardSize)
        throw rangeError("Bad value in IsBlank");

    // Return true if value is blank, else return false
    if (value[i][j] == blank)
        return true;
    else
        return false;
}


// Print function - Displays the current state of the board in a readable format.
void Board::Print() {
    for (int i = 1; i <= boardSize; i++) {
        if ((i - 1) % squareSize == 0) {
            cout << " -";
            for (int j = 1; j <= boardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= boardSize; j++) {
            if ((j - 1) % squareSize == 0)
                cout << "|";
            if (!IsBlank(i, j))
                cout << " " << GetCell(i, j) << " ";
            else
                cout << "   ";
        }
        cout << "|";
        cout << endl;
    }

    cout << " -";
    for (int j = 1; j <= boardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
}


// IsSolved function - Checks if the board is completely solved.
bool Board::IsSolved() {
    int i, j;
    // If any of the conflicts has a false, return false
    for (i = 1; i <= boardSize; i++) {
        for (j = 1; j <= boardSize; j++) {
            if (!rowConflicts[i][j] || !colConflicts[i][j] ||
                !sqConflicts[i][j]) {
                return false;
            }
        }
    }
    return true;
}


// PrintConflicts function -  Outputs the current conflict states for rows, 
// columns, and squares.
void Board::PrintConflicts() {
    int i;
    // Print the row conflicts
    cout << "Rows: ";
    for (int r = 1; r <= boardSize; r++) {
        cout << endl << "Row " << r << ": ";
        for (i = 1; i <= boardSize; i++) {
            cout << rowConflicts[r][i] << " ";
        }
    }

    // Print the columns conflicts
    cout << endl << "Columns: ";
    for (int c= 1; c <= boardSize; c++) {
        cout << endl << "Column " << c << ": ";
        for (i = 1; i <= boardSize; i++) {
            cout << colConflicts[c][i] << " ";
        }
    }

    // Print the square conflicts
    cout << endl << "Squares: ";
    for (int s = 1; s <= boardSize; s++) {
        cout << endl << "Square " << s << ": ";
        for (i = 1; i <= boardSize; i++) {
            cout << sqConflicts[s][i] << " ";
        }
    }
    cout << endl;
} // End PrintConflicts


// SetCell & ClearCell functions - Modify cell values and update conflict status.

// Sets cell i,j to val and update conflicts
void  Board::SetCell(int i, int j, ValueType val) {
    //Throw error if out of board range
    if (i < 1 || i > boardSize || j < 1 || j > boardSize)
        throw rangeError("Bad value in SetCell");
    // Sets the value
    value[i][j] = val;
    // If val is not blank, add conflict
    if (val != blank) {
        AddConflict(i, j, val);        // Manage conflict tracking for each cell.
    }
}

// Clears cell i, j and update conflicts
// Assumes there is no other cell causing conflict in it's row, col, or square
void Board::ClearCell(int i, int j) {
    // Throw error if out of board range
    if (i < 1 || i > boardSize || j < 1 || j > boardSize)
        throw rangeError("Bad value in ClearCell");

    int oldValue = value[i][j]; //Save old value
    // If the old value is not blank change value to blank and remove conflict
    if (oldValue != blank && oldValue != 0) {
        value[i][j] = blank;
        RemoveConflict(i, j, oldValue);   // Manage conflict tracking for each cell.
    }
}


// CausesConflict function - Determines if placing a value in a cell causes any 
// conflicts. Returns if adding value to cell[i][j] would cause a conflict
bool Board::CausesConflict(int i, int j, ValueType val) {
    // Throw error if out of board range
    if (i < 1 || i > boardSize || j < 1 || j > boardSize ||
        val < minValue || val > maxValue)
        throw rangeError("Bad value in CausesConflict");

    int s = SquareNumber(i, j); //Get the square number
    // Return true if there is a conflict in one of the matrices
    return rowConflicts[i][val] && colConflicts[j][val] && sqConflicts[s][val];
}

// Adds a conflict for cell[i][j]
void Board::AddConflict(int i, int j, ValueType val) {
    //Throw error if out of board range
    if (i < 1 || i > boardSize || j < 1 || j > boardSize ||
        val < minValue || val > maxValue)
        throw rangeError("Bad value in CausesConflict");

    int s = SquareNumber(i, j); //Get the square number
    //Update conflict matrices
    rowConflicts[i][val] = true;
    colConflicts[j][val] = true;
    sqConflicts[s][val] = true;
}

// Removes conflicts for cell[i][j]
void Board::RemoveConflict(int i, int j, ValueType val) {
    //Throw error if out of board range
    if (i < 1 || i > boardSize || j < 1 || j > boardSize ||
        val < minValue || val > maxValue)
        throw rangeError("Bad value in CausesConflict");

    int s = SquareNumber(i, j); //Get square number
    //Update conflict matrices
    rowConflicts[i][val] = false;
    colConflicts[j][val] = false;
    sqConflicts[s][val] = false;
}

// isLegal function - Checks if a value can be legally placed in a cell.
// Checks if a given digit (v) can be placed in a given cell (i, j)
bool Board::IsLegal(int i, int j, int v)
{
   int sqr = (j+2)/3 + ((i-1)/3)*3;
   
   // Considered legal if the value hasn't been tried yet and there are no conflicts
   if (!(rowConflicts[i][v] or colConflicts[j][v] or sqConflicts[sqr][v]))
      return true;
   else
      return false;     
}

// nextCell function - Finds the next empty cell to fill.
bool Board::NextCell(int &i, int &j)
{
   // check each cell (i, j) for number of conflicts
   for (i = 1; i <= boardSize; i++)
   {
      for (j = 1; j <= boardSize; j++)
      {
         if(IsBlank(i,j))
            return true;
      }
   }
   return false;
} // End nextCell


// solve function - Main recursive function for solving the Sudoku puzzle. It 
// employs a backtracking algorithm.
bool Board::Solve(int &count)
{
   count++;
   int row = 0;
   int col = 0;
   // If there are no empty cells, the sudoku is solved

   if(!NextCell(row, col)) // gets the next row and col to fill in
   {
      // return the solved board and exit
      Print();
      return true;
   }
   else
   {
      // checks for legal digits in next empty cell
      for (int v = 1; v <= boardSize; v++)
      {
         // if there is a candidate
         if(IsLegal(row, col, v))
         {
            // fill the cell
            SetCell(row, col, v);
            if(Solve(count)) // next recursive call, checks if the puzzle is solved
            {
               // prints count & exits
               // cout << count << endl;
               recursions = count;
               return true;
            }
            // if puzzle is not solved, clear the most recent cell
            ClearCell(row, col);
         }
      }
   }
   return false;
} // End of solve

// getRecursions function - Returns the number of recursive calls made during
//  the solving process.
int Board::GetRecursions()
{
   return recursions;
}
