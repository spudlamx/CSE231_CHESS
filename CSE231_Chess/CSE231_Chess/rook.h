//
//  rook.h
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#ifndef rook_h
#define rook_h

#pragma once
#include "piece.h"

class Rook : public Piece{
public:
    Rook(int r, int c, bool iswhite) : Piece(r, c, iswhite) {}
    char getLetter() const { return 'r'; }
    set<Move> getMoves (const Board & board) const;
    virtual void display(ogstream* pgout) const
    {
        pgout->drawRook(position.getLocation(), !isWhite());
    }
};


#endif /* rook_h */
