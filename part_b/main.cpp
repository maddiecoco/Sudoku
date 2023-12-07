#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <tuple>
#include "d_matrix.h"
#include "d_except.h"
#include "board.h"

using namespace std;

int main() {

    ifstream fin;
    ifstream g2;
    ifstream g3;
    std::vector<Board> boards;

    // Read in grids from files
    string fileName = "sudoku.txt";

    Board b1(squareSize);

    int total = 0;
    int avg = 0;
    int count = 0;

    // Error message if file can't be opened
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    while (fin && fin.peek() != 'Z')
    {
        count = count + 1;
        b1.Initialize(fin);
        // Print original boards and solved boards
        cout << "Board " << count << " unsolved:" << endl;
        b1.Print();
        cout << "Board " << count << " solved:" << endl;
        int countb1 = 0;
        b1.solve(countb1);
        total = total + b1.getRecursions();
        boards.push_back(b1);
    } 

    cout << endl << "Recursion Data:" << endl;
    for (int i = 0; i < boards.size(); i++)
    {
        cout << "Recursive calls for board " << i + 1 << ": " << boards[i].getRecursions() << endl;
    }
    
    avg = total / boards.size();
    cout << "Average recursive calls: " << avg << endl;
    cout << "All done!" << endl;
    return 0;
}
