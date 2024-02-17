//
//  knight.h
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#ifndef knight_h
#define knight_h

#pragma once
#include "piece.h"

class Knight : public Piece{
public:
    Knight(int r, int c, bool iswhite) : Piece(r, c, iswhite) {}
    char getLetter() const { return 'q'; }
    set<Move> getMoves (const Board & board) const;
    virtual void display(ogstream* pgout) const
    {
        pgout->drawKnight(position.getLocation(), !isWhite());
    }
};


#endif /* knight_h */
