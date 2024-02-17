//
//  rook.cpp
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#include <stdio.h>
#include "rook.h"
#include "board.h"

set<Move> Rook::getMoves(const Board& board) const {
    // Define rook deltas
    const Delta rookDeltas[] = {
        {0, 1},  // right
        {0, -1}, // left
        {1, 0},  // down
        {-1, 0}  // up
    };

    // Number of deltas for a rook
    const int numRookDeltas = sizeof(rookDeltas) / sizeof(rookDeltas[0]);

    return getMovesSlide(board, rookDeltas, numRookDeltas);
}
