// Maddie & Neha
// Sudoku Puzzle Part B


// Standard libraries, input/output operations, file handling, and standard functions used.
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <tuple>
#include "d_matrix.h"
#include "d_except.h"
#include "board.h"

using namespace std;    // Makes standard library names available.

// main function
int main() {

    // Variable initialization and declaration
    ifstream fin;
    ifstream g2;
    ifstream g3;
    std::vector<Board> boards;

    // Opens the Sudoku text file and reads in grids
    string fileName = "sudoku.txt";

    Board b1(squareSize);

    int total = 0;
    int avg = 0;
    int count = 0;

    // Error message - Exits the program with an error message if the file cannot be opened.
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    while (fin && fin.peek() != 'Z')    // Reads Sudoku boards from the file within a while loop that continues
                                        // until it encounters 'Z' or reaches the end of the file.
    {
        count = count + 1;
        b1.Initialize(fin);        // Initializes the board
        cout << "Board " << count << " unsolved:" << endl;
        b1.Print();
        cout << "Board " << count << " solved:" << endl;
        int countb1 = 0;
        b1.Solve(countb1);
        total = total + b1.GetRecursions();
        boards.push_back(b1);
    } 

    cout << endl << "Recursion Data:" << endl;
    for (int i = 0; i < boards.size(); i++)
    {
        cout << "Recursive calls for board " << i + 1 << ": " << boards[i].GetRecursions() << endl;
    }

    // Calculates and prints the average number of recursive calls across all boards.
    avg = total / boards.size();
    cout << "Average recursive calls: " << avg << endl;
    cout << endl << "All done!" << endl;
    return 0;
}
