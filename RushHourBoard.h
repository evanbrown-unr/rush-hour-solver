/**
 * @file RushHourBoard.h
 * @author Evan Brown
 *         Andrew Cooper
 *         Erik Johnson
 * @brief Rush Hour board header file.
 * @version 2.00
 * @date 12/4/17
 */



#include <string>



#ifndef RUSHHOURBOARD_H
#define RUSHHOURBOARD_H



class RushHourBoard
{
    public:
        RushHourBoard();

        // Getters
        int getNumMoves() const;

        // Board functionalities
        bool createBoard();
        void solve();
        bool isSolved() const;
        bool moveForward(int i);
        bool moveBackward(int i);

        // Used for debugging/visual
        void printBoard() const;

    private:
        struct Vehicle
        {
            int rowPos;     ///< y coordinate for back of vehicle
            int colPos;     ///< x coordinate for back of vehicle
            int length;     ///< 2 = car, 3 = truck
            char direction; ///< 'H' = horizontal, 'V' = vertical
        };

        // Default values for game
        static const int MAXROW = 6;
        static const int MAXCOL = 6;
        // Theoretically the maximum number of vehicles
        //  that can be on a board.
        static const int MAXVEH = (MAXROW * MAXCOL) / 2;

        // Private helper methods
        bool moveExists(int row, int col) const;
        std::string boardToString() const;

        // Data members
        Vehicle vehicles[MAXVEH];   ///< array of vehicles
        int board[MAXROW][MAXCOL];  ///< Rush Hour game board
        int numRows;                ///< rows on board
        int numCols;                ///< columns on board
        int numMoves;               ///< number of moves for solution
        int numVehicles;            ///< number of vehicles on board
};



#endif // RUSHHOURBOARD_H
