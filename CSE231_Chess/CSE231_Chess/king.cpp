//
//  king.cpp
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#include <stdio.h>
#include "king.h"
#include "board.h"

set<Move> King::getMoves(const Board& board) const {
    // Define king deltas for one-square moves in all directions
    const Delta kingDeltas[] = {
        {1, 0},   // Horizontal: one square right
        {-1, 0},  // Horizontal: one square left
        {0, 1},   // Vertical: one square up
        {0, -1},  // Vertical: one square down
        {1, 1},   // Diagonal: one square up, one square right
        {1, -1},  // Diagonal: one square up, one square left
        {-1, 1},  // Diagonal: one square down, one square right
        {-1, -1}  // Diagonal: one square down, one square left
    };

    // Number of deltas for a king
    const int numKingDeltas = sizeof(kingDeltas) / sizeof(kingDeltas[0]);

    // Calculate all possible non-sliding moves for the king
    set<Move> moves = getMovesNoslide(board, kingDeltas, numKingDeltas);

    // Check for castling
    if (position.getRow() == (isWhite()? 0:7) && !isMoved()) {
        for (int i = 0; i <= 7; i += 7) {
            int col = position.getCol();
            int row = position.getRow();
            Position target(row, i);

            // Check if the target square contains a rook and it hasn't moved
            if (board[target].getLetter() == 'r' && !board[target].isMoved()) {
                // Check if squares between king and rook are empty
                bool isPathClear = true;
                col > i ? col-- : col++;
                while (col != i) {
                    if (board[{row, col}].getLetter() != ' ') {
                        isPathClear = false;
                        break;
                    }
                    col > i ? col-- : col++;
                }

                // If path is clear, add castling move to the set of possible moves
                if (isPathClear) {
                    Move move;
                    move.setSrc(position);
                    move.setDes({row, (position.getCol() + (target.getCol() > position.getCol()? 2:-2))});
                    move.setCastle(i != 0);
                    moves.insert(move);
                }
            }
        }
    }

    // Return the set of all possible moves
    return moves;
}
