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

// ... (include necessary headers)

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
    // Implement the logic for space moves
    // Spaces don't have moves, so return an empty set
    return {};
}

set<Move> Rook::getMoves(const Board& board) const {
    // Define rook deltas (assuming horizontal and vertical moves)
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


