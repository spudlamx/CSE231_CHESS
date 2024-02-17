//
//  pawn.h
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#ifndef pawn_h
#define pawn_h

#pragma once
#include "piece.h"


class Pawn : public Piece{
public:
    Pawn(int r, int c, bool iswhite) : Piece(r, c, iswhite) {}
    char getLetter() const { return 'p'; }
    set<Move> getMoves (const Board & board) const;
    virtual void display(ogstream* gout) const
    {
        gout->drawPawn(position.getLocation(), !isWhite());
    }
private:
    void addPromotion(set <Move> & moves, Move & move) const;
};



#endif /* pawn_h */
