//
//  knight.cpp
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#include <stdio.h>
#include "knight.h"
#include "board.h"

set<Move> Knight::getMoves(const Board& board) const {
    // Define knight deltas (assuming L-shaped moves)
    const Delta knightDeltas[] = {
        {2, 1},   // L-shape: two squares up, one square right
        {1, 2},   // L-shape: one square up, two squares right
        {-1, 2},  // L-shape: one square down, two squares right
        {-2, 1},  // L-shape: two squares down, one square right
        {-2, -1}, // L-shape: two squares down, one square left
        {-1, -2}, // L-shape: one square down, two squares left
        {1, -2},  // L-shape: one square up, two squares left
        {2, -1}   // L-shape: two squares up, one square left
    };

    // Number of deltas for a knight
    const int numKnightDeltas = sizeof(knightDeltas) / sizeof(knightDeltas[0]);
    return getMovesNoslide(board, knightDeltas, numKnightDeltas);
}
