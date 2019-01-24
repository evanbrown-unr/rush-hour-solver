/**
 * @file RushHourMain.cpp
 * @author Evan Brown
 *         Andrew Cooper
 *         Erik Johnson
 * @brief Rush Hour solver main function.
 * @details In this game, there is a 6x6 board that is filled with both cars
 *  and trucks, with lengths of 2 and 3 respectively. They can either be
 *  horizontally or vertically oriented, and can only move forward and
 *  backward. The goal of the game is to clear the traffic jam to get
 *  the red car (the 0th car) across the board. The program finds the
 *  minimum number of moves to a Rush Hour configuration in optimal time
 *  using a breadth-first search until the solution is found.
 * @version 2.00
 * @date 12/4/17
 */



#include <iostream>
#include "RushHourBoard.h"


// Used for showing the board state
//  before and after solving it.
static const bool SHOW_BOARD = false;

int main()
{
    for (int index = 1; true; index++)
    {
        RushHourBoard board;
        if (!board.createBoard()) return 0;

        if (SHOW_BOARD)
        {
            std::cout << "BEFORE SOLVING..." << std::endl;
            board.printBoard();
        }

        board.solve();

        if (SHOW_BOARD)
        {
            std::cout << "AFTER SOLVING..." << std::endl;
            board.printBoard();
        }

        std::cout << "Scenario " << index
             << " requires " << board.getNumMoves()
             << " moves" << std::endl;
    }
}
