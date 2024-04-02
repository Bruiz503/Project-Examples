/* 
 * File:   AmazeMain.cpp
 * Author: Brandon Ruiz
 * Credits:
 *     Some mazes generated via https://www.dcode.fr/maze-generator
 *
 * Create and solve a maze.
 *      Can use a stack and/or queue implementation.
 */

#include <cstdlib>
#include <iostream>
#include <limits>

#include "Maze.h"

using namespace std;

int inputInteger(string promptText, int low, int high);   // Prompt for an integer until the user enters one

int main() {
    // Do "Press any key to continue..." on exit
    atexit([] {system("pause");});

    // Define constants for the characters that describe the maze.
    const char OPEN = ' ';
    const char WALL = 'X';
    const char FINISH = 'F';

    // Default 10x10 maze
    const int maze1_rows = 10;
    const int maze1_cols = 10;
    char maze1[]{
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, FINISH,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL
    };

    // Larger 16x20 maze
    const int maze2_rows = 16;
    const int maze2_cols = 20;
    char maze2[] = {
        OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN,
        OPEN, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, OPEN,
        OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN,
        OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, WALL, FINISH, WALL, WALL, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN,
        OPEN, WALL, WALL, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN,
        OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN,
        OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN,
        OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN

    };

    // This maze does not contain a finish so is unsolvable.
    // Use to test whether you are actually traversing the whole maze.
    // Output should be the maze with all open spaces marked as visited.
    const int maze3_rows = 10;
    const int maze3_cols = 10;
    char maze3[] = {
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
        OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL
    };

    // Largest 39x41 maze
    const int maze4_rows = 39;
    const int maze4_cols = 41;
    char maze4[] = {
    OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
    WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
    WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL,
    WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
    WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL,
    WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, FINISH, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
    WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL,
    WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL,
    WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL,
    WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, WALL,
    WALL, WALL, WALL, WALL, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, OPEN, WALL, WALL, WALL, WALL, WALL,
    WALL, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, WALL, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN, OPEN
    };

    int rows = 0;
    int cols = 0;
    char* maze = nullptr;
    int choice;

    cout << "Maze choices are:\n";
    cout << " 1 - Default 10x10 maze\n";
    cout << " 2 - Larger 16x20 maze\n";
    cout << " 3 - Unsolvable maze\n";
    cout << " 4 - Larger 39x41 maze\n";

    choice = inputInteger("Enter Choice: ", 1, 4);

    if (choice == 1) {
        rows = maze1_rows;
        cols = maze1_cols;
        maze = maze1;
    }
    else if (choice == 2) {
        rows = maze2_rows;
        cols = maze2_cols;
        maze = maze2;
    }
    else if (choice == 3) {
        rows = maze3_rows;
        cols = maze3_cols;
        maze = maze3;
    }
    else if (choice == 4) {
        rows = maze4_rows;
        cols = maze4_cols;
        maze = maze4;
    }

    // Make a copy so we do not corrupt the first.  
    // This will be changed by first attempt to solve via stack.
    // The original will be changed by the second attempt to solve via queue.
    char* to_change = new char[rows * cols];
    std::copy(&maze[0], &maze[0] + rows * cols, &to_change[0]);

    // Declare b as an array of pointers to characters.
    // It is not a two-dimensional array of characters like maze1 and to_change.
    // Use b because its elements can be referenced like a two-dimensional array as b[r][c].
    char** b = new char* [rows];
    for (int r = 0; r < rows; r++)
        b[r] = &to_change[r * cols];

    //////////////////////////////////////////////////////////////////////////////

    Maze game;    // Do stack first          

    game.set_maze(b, rows, cols);
    game.print();                    // Make sure its right.

    bool solved = game.solve_with_stack();
    if (solved == true) cout << "\nYEAH! solved with stack!\n\n";
    else cout << "\nBOO! can't solve with stack!\n\n";
    game.print();


    //////////////////////////////////////////////////////////////////////////////

    Maze game2;    // Do queue next

    for (int r = 0; r < rows; r++)
        b[r] = &maze[r * cols];

    game2.set_maze(b, rows, cols);

    game2.print();

    solved = game2.solve_with_queue();
    if (solved == true) cout << "\nYEAH! solved with queue!\n\n";
    else cout << "\nBOO! can't solve with queue!\n\n";

    game2.print();

    return 0;
}

// inputInteger - displays a prompt given by the promptText parameter and 
// returns an integer read from the console.
// 
// If something other than an integer within the low/high range is entered at the console, 
// this function displays "Invalid input" and prompts again.  Input following the integer up to
// the newline is read and ignored.
//
int inputInteger(string promptText, int low, int high)
{
    int val;
    int isFail;

    do {
        // Prompt the user for input 
        cout << promptText;
        // Attempt to read an integer
        cin >> val;
        // If the read failed or the integer isn't followed 
        // immediately by newline, record failure.
        isFail = cin.fail() || cin.peek() != '\n';
        // Clear errors on cin to setup for the next read.
        cin.clear();
        // Remove everything left in the buffer up to the newline.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Report an error for failure.
        if (val < low || val > high) isFail = true;
        if (isFail) {
            cout << "Invalid input\n";
        }
    } while (isFail);  // Loop until successful

    return val;
} // end function inputInteger
