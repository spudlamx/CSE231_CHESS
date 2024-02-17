//
//  queen.cpp
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#include <stdio.h>
#include "queen.h"
#include "board.h"

set<Move> Queen::getMoves(const Board& board) const {
    // Define queen deltas (combining rook and bishop moves)
    const Delta queenDeltas[] = {
        {1, 0},   // Horizontal: one square right
        {-1, 0},  // Horizontal: one square left
        {0, 1},   // Vertical: one square up
        {0, -1},  // Vertical: one square down
        {1, 1},   // Diagonal: one square up, one square right
        {1, -1},  // Diagonal: one square up, one square left
        {-1, 1},  // Diagonal: one square down, one square right
        {-1, -1}  // Diagonal: one square down, one square left
    };

    // Number of deltas for a queen
    const int numQueenDeltas = sizeof(queenDeltas) / sizeof(queenDeltas[0]);

    return getMovesSlide(board, queenDeltas, numQueenDeltas);
}
