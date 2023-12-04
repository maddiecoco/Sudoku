#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

int main() {
    ifstream fin;

    //Read the sample grid from the file.
    string fileName = "sudoku.txt";


    //Open file and check that it opened
    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try {
        Board b1(squareSize);

        //For each board in file
        while (fin && fin.peek() != 'Z') {
            b1.Initialize(fin); //initalize board
            b1.Print(); //Print board
            b1.PrintConflicts(); //Print Conflicts
            cout << "Solved: " << b1.IsSolved() << endl; //Print IsSolved
        }
    }


    //Catch range errors
    catch (indexRangeError &ex) {
        cout << ex.what() << endl;
        exit(1);
    }


    //Waits for the user to exit
    cout << "Press any key and enter to exit" << endl;
    string exit;
    cin >> exit;
}
