
#pragma once

#include "position.h"   // for POSITION: how we locate pieces
#include "move.h"       // for MOVE: how we move pieces around
#include "piece.h"      // for PIECE: what the board consists of
#include "uiInteract.h"

// Forward declarations

class Move;


class Board
{
public:
   
   // Test suites with private access
   friend class testBoard;
   
   // Constructor & Destructor
    Board(Interface* pUi, bool noReset = false) : currentMove(-1){
        pgout = new ogstream;
        if (!noReset)
           reset(false /*fFree*/);
    }
   ~Board()
   {
      free();
   }
   
   // Accessors
   int getCurrentMove() const { return currentMove;            }
   bool isWhiteTurn()   const { return currentMove % 2 == 0;   }
   void display(const Position & posHover, const Position & posSelect) const;
   const Piece & operator [] (const Position & pos) const
   {
      return * board[pos.getRow()][pos.getCol()];
   }
   
   // Mutators
   void free();
   virtual void reset(bool fFree = true);
    void testBoard(bool fFree = true);
    void assign(const Piece& piece, const Position& pos);
    void move(const Move & move);
   void operator -= (const Position & pos);
   void operator -= (const Move & move);
   void remove(const Position & pos);
   const Piece * operator = (Piece * rhs);
   Piece& operator [] (const Position & pos)
   {
      return * board[pos.getRow()][pos.getCol()];
   }
   void swap(const Position & pos1, const Position & pos2);
   void setCurrentMove(int currentMove) { this->currentMove = currentMove; }
   
protected:
   void assertBoard();
   
   Piece * board[8][8];      // The chess board of pieces
   int currentMove;          // The current move number we are on
   ogstream * pgout;         // The interface
};
