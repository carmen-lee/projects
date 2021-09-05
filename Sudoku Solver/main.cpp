/*
* Carmen Lee
* Description:  This program will solve a sudoku puzzle using brute force and recursion backtracking.
* Input:        Prompt the user for the input file that contains the initial sudoku puzzle
* Output:       Outputs the initial puzzle and then the solved puzzle
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
* function_identifier: uses recursive backtracking to solve sudoku board
* parameters: board, row, column
* return value: true for a solved board, false to backtrack
*/
bool sudoku (int board[][9], int r, int c) {
    /* Assign for next call */
    int row = r, col = c;
    if (c+1 == 9) {
        row++;
        col = 0;
    } else {
        col++;
    }
    /* Determine if puzzle is solved*/
    if (r == 9) {
        return true;
    }
    /* Populated Cell */
    if (board[r][c] != 0)
    {
        return sudoku(board, row, col);
    } else {
    /*  Unpopulated Cell */
        int n;
        bool found;
        /* Find n */
        for (n = 1 ; n <10 ; n++) {
            found = false;
            // column by column traversal
            for (int j = 0 ; j < 9 ; j++) {
                if (board[r][j] == n) {
                    found = true;
                }
            }
            // row by row traversal
            for (int i = 0 ; i < 9 ; i++) {
                if (board[i][c] == n) {
                    found = true;
                }
            }
            // sector
            int rMin = (r/3)*3 ,  rMax = ((r/3)*3)+3;
            int cMin = (c/3)*3 ,  cMax = ((c/3)*3)+3;
            for (int i = rMin ; i < rMax ; i++) {
                for (int j = cMin ; j < cMax ; j++)
                {
                    if (board[i][j] == n) {
                        found = true;
                    }
                }
            }
            // assign if x is not found
            if (!found) {
                board[r][c] = n;
                if (sudoku(board, row, col)) {
                    return true;
                }
            }
            board[r][c] = 0;
        }
        return false;
    }
}

int main() {
    string filename;
    bool recurse;
    
    do {
        cout << endl;
        /* Open File */
        ifstream puzzlefile;
        do {
            cout << "Enter initial sudoku board file: ";
            cin >> filename;
            if (filename == "NO")
                return 0;
            puzzlefile.open(filename);
        } while(puzzlefile.fail());

        /* Print and Initialize Board */
        int board[9][9];       
        int horizontalSector = 0;
        int verticalSector = 0;
        cout << "\nInitial board read in\n" << endl;
        cout << "-------------------------------------" << endl;
        for (int row = 0 ; row < 9 ; row++) {
            if (horizontalSector >= 3) {
                cout << "-------------------------------------" << endl;
                horizontalSector =0;
            }
            cout << "| ";
            for (int col = 0 ; col < 9 ; col++) {
                puzzlefile >> board[row][col];
                if (board[row][col] == 0) {
                    cout << " - ";
                } else {
                    cout << " " << board[row][col] << " ";
                }
                verticalSector++;
                if (verticalSector >= 3) {
                    cout << " | ";
                    verticalSector = 0;
                }
            }
            cout << endl;
            horizontalSector++;
        }
        cout << "-------------------------------------" << endl;
        puzzlefile.close();
        
        recurse = sudoku(board, 0, 0);

        if (recurse) {
            cout << "\nSudoku puzzled solved\n" << endl;
            horizontalSector = 0;
            cout << "-------------------------------------" << endl;
            for (int row = 0 ; row < 9 ; row++) {
                if (horizontalSector >= 3) {
                    cout << "-------------------------------------" << endl;
                    horizontalSector =0;
                }
                cout << "| ";
                for (int col = 0 ; col < 9 ; col++) {
                    if (board[row][col] == 0) {
                        cout << " - ";
                    } else {
                        cout << " " << board[row][col] << " ";
                    }
                    verticalSector++;
                    if (verticalSector >= 3) {
                        cout << " | ";
                        verticalSector = 0;
                    }
                }
                cout << endl;
                horizontalSector++;
            }
            cout << "-------------------------------------" << endl; 
        }
    } while (filename != "NO");
    return 0;
}