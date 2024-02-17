#include "piece.h"
#include "board.h"
#include "cassert"
#include "iostream"

const Piece& Piece::operator=(const Piece& rhs) {
    if (this != &rhs) {
        // Copy member variables from rhs to *this
        fWhite = rhs.fWhite;
        nMoves = rhs.nMoves;
        position = rhs.position;
        lastMove = rhs.lastMove;
    }
    return *this;
}


set<Move> Piece::getMovesSlide(const Board& board, const Delta deltas[], int numDelta) const {
    set<Move> moves;

    for (int i = 0; i < numDelta; ++i) {
        int newRow = position.getRow() + deltas[i].dRow;
        int newCol = position.getCol() + deltas[i].dCol;
        Position dest(newRow, newCol);

        while (dest.isValid()) {
            // Check if the destination position is occupied by a piece of the same color
            if (board[dest].isWhite() == fWhite && board[dest].getLetter() != ' ') {
                break;  // Can't move through or capture own piece
            }

            Move move;  // Use default constructor
            move.setSrc(Position(position));  // Set source position
            move.setDes(dest);  // Set destination position
            if (board[dest].isWhite() != isWhite() && board[dest].getLetter() != ' ') {
                move.setCapture(move.pieceTypeFromLetter(board[dest].getLetter()));
            }
            moves.insert(move);

            // If the destination position is occupied by an opponent's piece, stop sliding
            if (board[dest].getLetter() != ' ') {
                break;
            }

            // Move to the next position in the specified direction
            newRow += deltas[i].dRow;
            newCol += deltas[i].dCol;
            dest.set(newRow, newCol);  // Update the destination position
        }
    }

    return moves;
}




set<Move> Piece::getMovesNoslide(const Board& board, const Delta deltas[], int numDelta) const {
    set<Move> moves;
    
    for (int i = 0; i < numDelta; ++i) {
        int newRow = position.getRow() + deltas[i].dRow;
        int newCol = position.getCol() + deltas[i].dCol;
        Position dest(newRow, newCol);
        
        if (dest.isValid()) {
            // Check if the destination position is occupied by a piece of the same color
            if (board[dest].isWhite() != fWhite || board[dest].getLetter() == ' ') {
                // Can't move through or capture own piece
                Move move;  // Use default constructor
                move.setSrc(Position(position));  // Set source position
                move.setDes(dest);  // Set destination position
                if (board[dest].isWhite() == !isWhite() && board[dest].getLetter() != ' '){
                    move.setCapture(move.pieceTypeFromLetter(board[dest].getLetter()));
                }
                moves.insert(move);
            }
            
        }
        
       
    }
    return moves;
};


set<Move> Space::getMoves(const Board& board) const {
    return {};
}

