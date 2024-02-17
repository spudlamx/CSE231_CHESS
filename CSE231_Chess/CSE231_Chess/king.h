//
//  king.h
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#ifndef king_h
#define king_h

#pragma once
#include "piece.h"

class King : public Piece{
public:
    King(int r, int c, bool iswhite) : Piece(r, c, iswhite) {}
    char getLetter() const { return 'k'; }
    set<Move> getMoves (const Board & board) const;
    virtual void display(ogstream* pgout) const
    {
        pgout->drawKing(position.getLocation(), !isWhite());
    }
};

#endif /* king_h */
