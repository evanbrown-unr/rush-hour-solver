/**
 * @file RushHourBoard.cpp
 * @author Evan Brown
 *         Andrew Cooper
 *         Erik Johnson
 * @brief Rush Hour board implementation file.
 * @version 2.00
 * @date 12/4/17
 */



#include <iostream>
#include <queue>
#include <unordered_map>

#include "RushHourBoard.h"



/**
 * @brief Default constructor.
 * @post Initializes all members and creates an empty board.
 */
RushHourBoard::RushHourBoard()
{
    numMoves = 0;
    numVehicles = 0;
    numRows = MAXROW;
    numCols = MAXCOL;

    for(int i = 0; i < numRows; i++)
        for(int j = 0; j < numCols; j++)
            board[i][j] = -1;
}



/**
 * @brief Gets the number of moves.
 * @return An integer for the number of moves on board.
 */
int RushHourBoard::getNumMoves() const
{
    return numMoves;
}



/**
 * @brief Reads in data for vehicles and places into board.
 *
 * First this function resets the board, in case there's more than one iteration.
 * Then, The data is read in for the various vehicles, and then they are placed on
 * the board in their location.

 * @post The game board is ready for play.
 * @return True if the game board is created correctly,
 * false if an error occurs.
 */
bool RushHourBoard::createBoard()
{
    std::cin >> numVehicles;
    if (numVehicles == 0) return false;

    for (int i = 0; i < numVehicles; i++)
    {
        std::cin >> vehicles[i].length
                 >> vehicles[i].direction
                 >> vehicles[i].rowPos
                 >> vehicles[i].colPos;

        if (!moveExists(vehicles[i].rowPos, vehicles[i].colPos))
            return false;

        board[vehicles[i].rowPos][vehicles[i].colPos] = i;

        if (vehicles[i].direction == 'H')
        {
            if (vehicles[i].length == 2)
            {
                if (!moveExists(vehicles[i].rowPos, vehicles[i].colPos+1))
                    return false;

                board[vehicles[i].rowPos][vehicles[i].colPos+1] = i;
            }

            if(vehicles[i].length == 3)
            {
                if ((!moveExists(vehicles[i].rowPos, vehicles[i].colPos+1)) ||
                    (!moveExists(vehicles[i].rowPos, vehicles[i].colPos+2)))
                    return false;

                board[vehicles[i].rowPos][vehicles[i].colPos+1] = i;
                board[vehicles[i].rowPos][vehicles[i].colPos+2] = i;
            }
        }

        else if (vehicles[i].direction == 'V')
        {
            if (vehicles[i].length == 2)
            {
                if (!moveExists(vehicles[i].rowPos+1, vehicles[i].colPos))
                    return false;

                board[vehicles[i].rowPos+1][vehicles[i].colPos] = i;
            }

            if (vehicles[i].length == 3)
            {
                if ((!moveExists(vehicles[i].rowPos+1, vehicles[i].colPos)) ||
                    (!moveExists(vehicles[i].rowPos+2, vehicles[i].colPos)))
                    return false;

                board[vehicles[i].rowPos+1][vehicles[i].colPos] = i;
                board[vehicles[i].rowPos+2][vehicles[i].colPos] = i;
            }
        }
    }

    return true;
}



/**
 * @brief Solves the Rush Hour game.
 * @details Uses a breadth-first search
 *  to solve the rush hour scenario.
 *  We use a queue to hold current states, and
 *  a map to hold states that have already been
 *  processed. This is to save time from solving
 *  scenarios we've already solved.
 */
void RushHourBoard::solve()
{
    std::queue<RushHourBoard> currStates;
    std::unordered_map<std::string,int> prevStates;

    if (isSolved())
        return;

    currStates.push(*this);
    prevStates[boardToString()] = numMoves;

    while (!currStates.empty())
    {
        *this = currStates.front();
        currStates.pop();
        numMoves = prevStates.find(boardToString())->second;

        if (isSolved())
            return;

        for (int i = 0; i < numVehicles; i++)
        {
            if (moveForward(i))
            {
                if (prevStates.count(boardToString()) == 0)
                {
                    currStates.push(*this);
                    prevStates[boardToString()] = numMoves + 1;
                }
                moveBackward(i);
            }

            if (moveBackward(i))
            {
                if (prevStates.count(boardToString()) == 0)
                {
                    currStates.push(*this);
                    prevStates[boardToString()] = numMoves + 1;
                }
                moveForward(i);
            }
        }
    }
}



/**
 * @brief Prints the current state of
 *  the board.
 * @details Used for debugging/visual
 *  purposes.
 */
void RushHourBoard::printBoard() const
{
    std::cout << "Rush Hour Board"
              << std::endl << "=================="
              << std::endl;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (board[i][j] == -1)
                std::cout << " -";
            else
                std::cout << ' ' << board[i][j];
        }
        std::cout << std::endl;
    }
}



/**
 * @brief Checks if location exists as valid move.
 * @param Takes two ints, row and col, representing
 * the coordinates of the move.
 * @return True if move is valid, false if it is not.
 */
bool RushHourBoard::moveExists(int row, int col) const
{
    return ((row >= 0) && (row < numRows) &&
            (col >= 0) && (col < numCols) &&
            (board[row][col] == -1));
}



/**
 * @brief Checks if the game has been solved.
 * @return True if the game is solved, false if it is not.
 */
bool RushHourBoard::isSolved() const
{
    return (vehicles[0].colPos + vehicles[0].length == numCols);
}



/**
 * @brief Move the vehicle forward.
 * @post If horizontal, the vehicle moves to the right, if vertical
 * it moves up.
 * @return True if valid move, false if it is not.
 */
bool RushHourBoard::moveForward(int i)
{
    if (vehicles[i].direction == 'H')
    {
        if ((vehicles[i].colPos + vehicles[i].length < numCols) &&
            (moveExists(vehicles[i].rowPos, vehicles[i].colPos + vehicles[i].length)))
        {
            board[vehicles[i].rowPos][vehicles[i].colPos] = -1;
            board[vehicles[i].rowPos][vehicles[i].colPos + vehicles[i].length] = i;
            vehicles[i].colPos++;
            return true;
        }

        return false;

    }

    else if (vehicles[i].direction == 'V')
    {
        if ((vehicles[i].rowPos + vehicles[i].length < numRows) &&
            (moveExists(vehicles[i].rowPos + vehicles[i].length, vehicles[i].colPos)))
        {
            board[vehicles[i].rowPos][vehicles[i].colPos] = -1;
            board[vehicles[i].rowPos + vehicles[i].length][vehicles[i].colPos] = i;
            vehicles[i].rowPos++;
            return true;
        }

        return false;
    }

    else return false;
}



/**
 * @brief Move the vehicle backward.
 * @post If horizontal, the vehicle moves to the left, if vertical
 * it moves down.
 * @return True if valid move, false if it is not.
 */
bool RushHourBoard::moveBackward(int i)
{
    if (vehicles[i].direction == 'H')
    {
        if ((vehicles[i].colPos - 1  >= 0) &&
            (moveExists(vehicles[i].rowPos, vehicles[i].colPos-1)))
        {
            board[vehicles[i].rowPos][vehicles[i].colPos+ vehicles[i].length-1] = -1;
            board[vehicles[i].rowPos][vehicles[i].colPos-1] = i;
            vehicles[i].colPos--;
            return true;
        }

        return false;
    }

    else if (vehicles[i].direction == 'V')
    {
        if ((vehicles[i].rowPos - 1 >= 0) &&
            (moveExists(vehicles[i].rowPos-1, vehicles[i].colPos)))
        {
            board[vehicles[i].rowPos + vehicles[i].length-1][vehicles[i].colPos] = -1;
            board[vehicles[i].rowPos-1][vehicles[i].colPos] = i;
            vehicles[i].rowPos--;
            return true;
        }

        return false;
    }

    else return false;
}



/**
 * @brief Converts current board state to
 *  a string.
 * @details Used for the BFS in solving the board.
 * @return A string that reprsents the
 *  state of the board.
 */
std::string RushHourBoard::boardToString() const
{
    std::string s;

    for (int i = 0; i  < numRows; i++)
        for (int j = 0; j < numCols; j++)
            s += board[i][j];

    return s;
}