/* 
 * File:   Maze.h
 * Author: Brandon Ruiz
 * This file contains the Maze class definition (interface).
 * See Maze.cpp for the Maze class implementation.
 */

#ifndef MAZE_H
#define MAZE_H

class Maze {
private:
    char ** amaze;            // The maze
    int rows;                 // Number of rows in the maze
    int cols;                 // Number of cols in the maze
    bool outside_or_wall_or_done(int row, int col); 
			      // Check if outside maze 
			      // or a wall or already searched
public:
    Maze();                   // constructor
    ~Maze();                  // destructor
    void set_maze (char ** maz, int numr, int numc);
    bool solve_with_stack();  // solves maze, possible routes are stacked        
    bool solve_with_queue();  // solves maze, possible routes are queued         
    void print ();            // prints current state of maze,
    // ' ' is open, 'X' is wall, 'F' is finish, 'o' is searched
};
#endif /* MAZE_H */

