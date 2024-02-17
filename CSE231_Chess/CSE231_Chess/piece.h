#pragma once
#include "position.h"
#include "move.h"
#include <set>
#include "uiDraw.h"

using namespace std;

class Board;

class Piece{
public:
    
    Piece(int r, int c, bool iswhite = true) : fWhite(iswhite), nMoves(0), position(r, c), lastMove(-1) {
        
    };
    Piece(const Piece & piece) {*this = piece; }
    virtual ~Piece() {}
    const Piece& operator = (const Piece& rhs);
    const Piece& operator = (const Position& rhs){
    nMoves++;
    position = rhs;
    return *this;
    }
    // getters
    bool operator == (char letter) const { return getLetter() == letter; } bool operator |= (char letter)
    const { return getLetter() == letter; };
    bool isWhite() const { return fWhite;}
    
    bool isMoved() const { return getNMoves() != 0;}
    int getNMoves() const { return nMoves;}
    void setNMoves(int moves) { nMoves = moves;}
    const Position & getPosition() const { return position;}
    bool justMoved(int currentMove) const{
        return
        (currentMove - 1 == lastMove);
    }
    // setter
    void setLastMove(int currentMove) { lastMove = currentMove; }
    // virtual methods
    virtual char getLetter() const = 0;
    
    virtual void display(ogstream * pgout) const = 0;
    
    virtual set<Move> getMoves(const Board & board) const = 0;
protected:
    set<Move> getMovesSlide(const Board & board, const Delta deltas[], int numDelta) const;
    set<Move> getMovesNoslide(const Board& board, const Delta deltas[], int numDelta) const;
    int nMoves;
    bool fWhite;
    Position position;
    int lastMove;

};
class Space : public Piece{
public:
    Space(int r, int c) : Piece(r, c, NULL) {}
    char getLetter() const { return ' '; }
    set<Move> getMoves (const Board & board) const;
    virtual void display(ogstream* pgout) const
    {}
};





