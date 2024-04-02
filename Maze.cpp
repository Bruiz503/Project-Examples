/* 
 * File:   Maze.cpp
 * Author: KM
 * Modified by: GL
 * This file contains the Maze class implementation.
 * See Maze.h for the Maze class definition (interface).
 */

#include <iostream>
#include <stack>
#include <queue>
#include "Maze.h"
//#include "LocStack.h"
//#include "LocQueue.h"

using namespace std;

// Constructor only initializes class variables.
Maze::Maze() { 
    rows = cols = 0;
    amaze = NULL;
}

// Destructor doesn't have anything to do but is left as a place holder
//      for any future features that need cleanup.
Maze::~Maze() {
    // Nothing to get rid of since we just point to the users supplied maze.
}

// Attach a users maze.  Keep track of number of rows and columns in it.
void Maze::set_maze (char ** maz, int numr, int numc) {
    rows = numr; 
    cols = numc; 
    amaze = maz;
}

// Determine if a row and column are outside the maze or 
//      if they are inside the maze but a wall or already searched.
//
// Returns:
//      true for outside, wall or already searched.
//      false if its inside, open and unsearched.
//
bool Maze::outside_or_wall_or_done(int r, int c) {
    // Any row or column that is negative is outside.
    // Any row or column that is greater than the values passed to set_maze are outside.
    if (r < 0 || c < 0 || r >= rows || c >= cols ) {    // Outside
        return true;
    }
    // ' ' is open, 'F' is the finish
    if (amaze[r][c] == ' ' || amaze[r][c] == 'F') { // not done, not wall
        return false;
    }
    // If we get here it is inside the maze but a wall or already done.
    return true;
}

// Location class declaration
// This class will hold the values of row and col that will then be added to 
// the stack and queue
class location {
public:
    // variables to hold the position of row and col
    int row;
    int col;

    // constructor to initialize an element of location with 2 arguments 
    location(int r, int c) { 
        row = r;
        col = c;
    };
};


// I will be using the stl library for this project, I find it's a good chance
// to get familiar with this library
// YOUR COMMENTS GO HERE
bool Maze::solve_with_stack () { 
    
    // create a stack using the stl library 
    stack<location> stacky;
    // create an element of the location class to hold the current location 
    // that the function is at
    location current(0, 0);

    // create two variables to hold the positions of row and col
    int row;
    int col;

    // start the function at the beginning of the maze (0,0) by pushing the
    // location on the stack
    stacky.push(location(0,0));

    // create a loop to step through the maze until it reaches the end, or 
    // all possible places to step to have been exhausted, signified by the 
    // stack being empty
    while (!stacky.empty()) {
        
        // update the current element to hold the value of the of the most recent 
        // location on the stack, then assign the according values to row and col
        current = stacky.top();
        row = current.row;
        col = current.col;
        // delete the top most value on the stack as we are now at that location
        // and do not need the value anymore
        stacky.pop();

        // check if the current location is the finish, if so, return true to 
        // signify we have made it to the end
        if (amaze[row][col] == 'F') {
            return true; 
        }

        // if we did not find the finish, that means we have step into and empty,
        // unexplored space, so change the value to o to signify when have now been
        // here
        amaze[row][col] = 'o';

        // using the function outside_or_wall_or_done, check to see if the
        // spaces next to our current location are spaces that are unexplored spaces available to move to, if so,
        // push the coordinates onto the stack
        if (!outside_or_wall_or_done(row - 1, col)) {
            stacky.push(location(row-1,col));
        }
        if (!outside_or_wall_or_done(row, col + 1 )) {
            stacky.push(location(row, col + 1 ));
        }
        if (!outside_or_wall_or_done(row + 1, col)) {
            stacky.push(location(row + 1, col));
        }
        if (!outside_or_wall_or_done(row, col - 1)) {
            stacky.push(location(row, col - 1));
        }
        
    }
    // If we did not find the end and we have searched all possible spaces
    // return false to signify that we did not find our beloved F
    return false;
}

// YOUR COMMENTS GO HERE
bool Maze::solve_with_queue () {

    // create a queue to hold the location elements
    queue<location> qtpi;

    // create a location object to hold the current front element values from the 
    // queue
    location current(0, 0);

    // start the maze at the beginning (0,0) by placing the coordinates onto the queue
    qtpi.push(location(0, 0));

    // while the queue still has coordinates to move to through, loop 
    while (!qtpi.empty()) {
        // create variables to hold the location coordinates pushed to the 
        // queue
        int row;
        int col;

        // assign the front coordinates of the queue to the location object,
        // then assigning the values to row and col
        current = qtpi.front();
        row = current.row;
        col = current.col;
        // delete the used coordinates 
        qtpi.pop();

        // if the current location is the finish, return true as we have made
        // it to the end
        if (amaze[row][col] == 'F') {
            return true;
        }
        // if we didn't reach the end, we've gotta be at an unexplored space,
        //  so change the blank value at the coordinates to o so we mark the space
        // as a place we have already been to
        amaze[row][col] = 'o';

        // using the function outside_or_wall_or_done, check to see if the
        // spaces next to our current location are spaces that are unexplored spaces available to move to, if so,
        // push the coordinates onto the queue

        if (!outside_or_wall_or_done(row, col + 1)) {
            qtpi.push(location(row, col + 1));
        }
        if (!outside_or_wall_or_done(row + 1, col)) {
            qtpi.push(location(row + 1, col));
        }
        if (!outside_or_wall_or_done(row, col - 1)) {
            qtpi.push(location(row, col - 1));
        }
        if (!outside_or_wall_or_done(row - 1, col)) {
            qtpi.push(location(row - 1, col));
        }

    }
    // If we did not find the end and we have searched all possible spaces
    // return false to signify that we did not find our beloved F
    // YOUR CODE GOES HERE
    return false;
}

// Print the current state of the maze.
// Maze if made up of chars where:
//              ' ' is open, 
//              'X' is wall, 
//              'F' is finish, 
//              'o' is already searched
//
void Maze::print () {
    for (int row =0; row <rows; row++) {
        for (int col =0; col <cols; col++) {
            cout << amaze[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}    


