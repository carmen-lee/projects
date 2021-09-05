/*
* Carmen Lee
* Description:  This program is a simulation of the 15 Puzzle game in terminal. Utilizes an array of 4 linked lists where 
*               each linked list will have 4 nodes and each node will be labelled 0 - 15.
* Input:        Requires a puzzle file of the board layout
* Output:       Outputs the game and allows users to interact with the board in order to win the game.
*/

#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
    char playAgain;
    char playerChoice;
    int rowCounter;
    int columnCounter;
    bool winCondition = false;
    LL<int>::iterator gap;
    LL<int>::iterator temp;
    LL <int>::iterator win;
    LL <int>::iterator it;

    do
    {
        /* Open File */
        char filename[50];
        ifstream puzzlefile;
        do
        {
            cout << "Enter puzzle file: ";
            cin >> filename;
            puzzlefile.open(filename);
        } while(puzzlefile.fail());

        /* Build Linked List */
        LL <int> board[4];
        int x;
        for (int row = 0 ; row < 4 ; row++)
        {
            for (int column = 0 ; column < 4 ; column++)
            {
                puzzlefile >> x;
                board[row].tailInsert(x);
            }
        }    
        puzzlefile.close();

        /* Print Game Board */
        cout << endl;
        for (int i = 0 ; i < 4 ; i++)
        {
            it = board[i].begin();
            for (int j = 0 ; j < 4 ; j++)
            {
                if (*it == 0)
                {
                    cout << "-" << "\t"; 
                }
                else
                {
                    cout << *it << "\t";
                }
                it++;
            }
            cout << endl;
        }

        do
        {
            /* Check for Win */
            winCondition = false;
            int counter = 1, numOfCorrectNodes = 0;
            for ( int i = 0 ; i < 4 ; i++)
            {
                win = board[i].begin();
                for (int j = 0 ; j < 4 ; j++)
                {
                    if (*win == counter)
                    {
                        numOfCorrectNodes++;
                    }
                    win++;
                    counter++;
                }
            }
            if (numOfCorrectNodes == 15)
            {
                winCondition = true;
            }

            if (!winCondition)
            {
                cout << "\nPlease make your choice, (L)eft, (R)ight, (U)p, (D)own, (Q)uit: ";
                cin >> playerChoice;
                cout << endl;
                if (playerChoice > 'Z') // case insensitive
                    playerChoice -= 32;
                switch (playerChoice)
                {
                    case 'L':
                    {
                        /* Find the Gap */
                        for (int i = 0 ; i < 4 ; i++)
                        {
                            gap = board[i].begin();
                            for (int j = 0 ; j < 4 ; j++)
                            {
                                if (*gap == 0)
                                {
                                    rowCounter = i;
                                    columnCounter = j;
                                    temp = gap;
                                    // cout << "gap: " << *gap << "\t" << "temp: " << *temp << endl;
                                }
                            gap++;
                            }
                        }
                        // cout << "location of the gap: " << rowCounter << "," << columnCounter << endl;
                        if (columnCounter != 3) //do nothing if the gap is in the rightmost position
                        {   // exchange its value with the node on the right
                            LL<int>::iterator target = temp;
                            LL<int>::iterator zero = temp;
                            int right = *zero++;
                            // cout << "temp node: " << *temp << endl;
                            // cout << "target node: " << *target << endl;
                            // cout << "zero node: " << *zero << endl;
                            // cout << "right element: " << right << endl;
                            board[rowCounter].update(target, right);
                            board[rowCounter].update(zero, 0);
                        }
                    }
                        break;

                    case 'R':
                    {
                        /* Find the Gap */
                        for (int i = 0 ; i < 4 ; i++)
                        {
                            gap = board[i].begin();
                            for (int j = 0 ; j < 4 ; j++)
                            {
                                if (*gap == 0)
                                {
                                    rowCounter = i;
                                    columnCounter = j;
                                    temp = gap;
                                    // cout << "gap: " << *gap << "\t" << "temp: " << *temp << endl;
                                }
                                gap++;
                            }
                        }
                        if (columnCounter != 0) //do nothing if the gap is in the leftmost position
                        {   // exchange its value with the node on the left
                            LL<int>::iterator target = temp;
                            LL<int>::iterator zero = temp;
                            int left = *zero--;
                            // cout << "temp node: " << *temp << endl;
                            // cout << "target node: " << *target << endl;
                            // cout << "zero node: " << *zero << endl;
                            // cout << "left element: " << left << endl;
                            board[rowCounter].update(target, left);
                            board[rowCounter].update(zero, 0);
                        }
                    }
                        break;

                    case 'U':
                    {
                        /* Find the Gap */
                        for (int i = 0 ; i < 4 ; i++)
                        {
                            gap = board[i].begin();
                            for (int j = 0 ; j < 4 ; j++)
                            {
                                if (*gap == 0)
                                {
                                    rowCounter = i;
                                    columnCounter = j;
                                    temp = gap;
                                    // cout << "gap: " << *gap << "\t" << "temp: " << *temp << endl;
                                }
                                gap++;
                            }
                        }
                        if (rowCounter != 3) //do nothing if the gap is in the bottom
                        {   // exchange its value with the node on the bottom
                            LL<int>::iterator target = temp;
                            LL<int>::iterator zero;
                            LL<int>::iterator traverse;
                            int findR, findC;
                            /* Find Node Below Gap */
                            for (int i = 0 ; i < 4 ; i++)
                            {
                                traverse = board[i].begin();
                                for (int j = 0 ; j < 4 ; j++)
                                {
                                    if (i==rowCounter+1 && j==columnCounter)
                                    {
                                        findR = i;
                                        findC = j;
                                        zero = traverse;
                                    }
                                    traverse++;
                                }
                            }
                            // cout << "location of the node below: " << findR << "," << findC << endl;
                            int below = *zero;
                            // cout << "temp node: " << *temp << endl;
                            // cout << "target node: " << *target << endl;
                            // cout << "zero node: " << *zero << endl;
                            // cout << "below element: " << below << endl;
                            board[columnCounter].update(target, below);
                            board[columnCounter].update(zero, 0);
                        }
                    }
                        break;
                    
                    case 'D':
                    {
                        /* Find the Gap */
                        for (int i = 0 ; i < 4 ; i++)
                        {
                            gap = board[i].begin();
                            for (int j = 0 ; j < 4 ; j++)
                            {
                                if (*gap == 0)
                                {
                                    rowCounter = i;
                                    columnCounter = j;
                                    temp = gap;
                                    // cout << "gap: " << *gap << "\t" << "temp: " << *temp << endl;
                                }
                                gap++;
                            }
                        }
                        if (rowCounter != 0) //do nothing if the gap is in the top row
                        {   // exchange its value with the node above
                            LL<int>::iterator target = temp;
                            LL<int>::iterator zero;
                            LL<int>::iterator traverse;
                            int findR, findC;
                            /* Find Node Below Above */
                            for (int i = 0 ; i < 4 ; i++)
                            {
                                traverse = board[i].begin();
                                for (int j = 0 ; j < 4 ; j++)
                                {
                                    if (i==rowCounter-1 && j==columnCounter)
                                    {
                                        findR = i;
                                        findC = j;
                                        zero = traverse;
                                    }
                                traverse++;
                                }
                            }
                            // cout << "location of the node above: " << findR << "," << findC << endl;
                            int above = *zero;
                            // cout << "temp node: " << *temp << endl;
                            // cout << "target node: " << *target << endl;
                            // cout << "zero node: " << *zero << endl;
                            // cout << "above element: " << above << endl;
                            board[columnCounter].update(target, above);
                            board[columnCounter].update(zero, 0);
                        }
                    }
                        break;

                    case 'Q':
                        cout << "Quitter..." << endl;
                        break;

                    default:    // repeat if invalid input was given
                        cout << "Invalid selection!" << endl;
                        break;

                }
                
                if (playerChoice != 'Q')
                {
                    /* Print Game Board */
                    cout << endl;
                    for (int i = 0 ; i < 4 ; i++)
                    {
                        it = board[i].begin();
                        for (int j = 0 ; j < 4 ; j++)
                        {
                            if (*it == 0)
                            {
                                cout << "-" << "\t"; 
                            }
                            else
                            {
                                cout << *it << "\t";
                            }
                            it++;
                        }
                        cout << endl;
                    }
                }
            }
            else
            {
                cout << "\nYou win!!!\n" << endl;
                for (int i = 0 ; i < 4 ; i++)
                {
                    board[i].~LL();     // deallocate the board to play again
                }
                do
                {
                    cout << "Play again? (Y/N): ";
                    cin >> playAgain;      
                    if (playAgain > 'Z') // case insensitive
                        playAgain -= 32;              
                } while(playAgain != 'N' && playAgain != 'Y');
            
                cout << endl;
            }
        } while (!winCondition && playerChoice != 'Q' && playAgain != 'N');
    } while (playerChoice != 'Q' && playAgain != 'N');

    if (playerChoice != 'Q')
    {
        cout << "\nYeah I don’t blame  you  for  not  wanting  to play  anymore" << endl;
        cout << "This  game is like  league ... except  it  actually  makes  sense :D\n" << endl;
    }

    return 0;
}