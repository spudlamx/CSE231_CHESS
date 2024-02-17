//
//  bishop.cpp
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#include <stdio.h>
#include "bishop.h"
#include "board.h"

set<Move> Bishop::getMoves(const Board& board) const {
    // Define bishop deltas (assuming diagonal moves)
    const Delta bishopDeltas[] = {
        {1, 1},   // Diagonal: one square up, one square right
        {1, -1},  // Diagonal: one square up, one square left
        {-1, 1},  // Diagonal: one square down, one square right
        {-1, -1}  // Diagonal: one square down, one square left
    };

    // Number of deltas for a bishop
    const int numBishopDeltas = sizeof(bishopDeltas) / sizeof(bishopDeltas[0]);

    return getMovesSlide(board, bishopDeltas, numBishopDeltas);
}
