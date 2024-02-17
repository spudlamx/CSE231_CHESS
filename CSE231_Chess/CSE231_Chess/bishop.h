//
//  bishop.h
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#ifndef bishop_h
#define bishop_h

#pragma once
#include "piece.h"

class Bishop : public Piece{
public:
    Bishop(int r, int c, bool iswhite) : Piece(r, c, iswhite) {}
    char getLetter() const { return 'b'; }
    set<Move> getMoves (const Board & board) const;
    virtual void display(ogstream* pgout) const
    {
        pgout->drawBishop(position.getLocation(), !isWhite());
    }
};

#endif /* bishop_h */
