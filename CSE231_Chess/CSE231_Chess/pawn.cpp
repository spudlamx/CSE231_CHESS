//
//  pawn.cpp
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#include <stdio.h>
#include "pawn.h"
#include "board.h"
set<Move> Pawn::getMoves(const Board& board) const {
    set<Move> moves;

    int forwardDirection = isWhite() ? 1 : -1;
    Position posMove(getPosition().getRow() + forwardDirection, getPosition().getCol());

    // Helper function to add moves
    auto addMove = [&](const Position& destination, bool isDoubleMove = false, bool isEnPassant = false) {
        Move move;
        move.setSrc(getPosition());
        move.setDes(destination);
        move.setWhiteMove(isWhite());
        move.setCapture(move.pieceTypeFromLetter(board[destination].getLetter()));
        

        // Check for promotion

        
        if (isEnPassant) {
            move.setEnPassant();
          }
        if (destination.getRow() == (isWhite() ? 7 : 0))
            addPromotion(moves, move);
        else
            moves.insert(move);
        if (isDoubleMove)
            return; // Double move doesn't have promotion
    };

    // Forward movement
    if (posMove.isValid() && board[posMove].getLetter() == ' ') {
        addMove(posMove);

        // Double move for the first move
        if (!isMoved() && position.getRow() == (isWhite()? 1:6)) {
            Position posDoubleMove(getPosition().getRow() + 2 * forwardDirection, getPosition().getCol());
            Position posCheck(getPosition().getRow() + forwardDirection, getPosition().getCol());

            if (board[posDoubleMove].getLetter() == ' ' && board[posCheck].getLetter() == ' ')
                addMove(posDoubleMove, true);
        }
    }

    // Single capture
    const int cDelta[] = { 1, -1 };
    for (int i = 0; i < 2; ++i) {
        Position posCapture(getPosition().getRow() + forwardDirection, getPosition().getCol() + cDelta[i]);
        if (posCapture.isValid() && board[posCapture].isWhite() == !isWhite() && board[posCapture].getLetter() != ' ')
            addMove(posCapture);
        
        // En Passant
        Position posEnPassant(getPosition().getRow() + forwardDirection, getPosition().getCol() + cDelta[i]);
        Position posKill(getPosition().getRow(), getPosition().getCol() + cDelta[i]);
        if (posEnPassant.isValid() && board[posEnPassant].getLetter() == ' ' &&
            board[posKill].isWhite() != isWhite() &&
            board[posKill].getNMoves() == 1 &&
            board[posKill].justMoved(board.getCurrentMove())) {
            addMove(posEnPassant, false, true);
        }
    }



    return moves;
}

void Pawn::addPromotion(set<Move>& moves, Move& move) const {
    // Implement the logic for pawn promotion
    // ...

    move.setPromote(QUEEN);
    moves.insert(move);
    return;
}


