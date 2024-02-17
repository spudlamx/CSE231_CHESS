//
//  queen.h
//  CSE231_Chess
//
//  Created by Spencer Lamoreaux on 2/16/24.
//

#ifndef queen_h
#define queen_h

#pragma once
#include "piece.h"

class Queen : public Piece{
public:
    Queen(int r, int c, bool iswhite) : Piece(r, c, iswhite) {}
    char getLetter() const { return 'q'; }
    set<Move> getMoves (const Board & board) const;
    virtual void display(ogstream* pgout) const
    {
        pgout->drawQueen(position.getLocation(), !isWhite());
    }
};

#endif /* queen_h */
