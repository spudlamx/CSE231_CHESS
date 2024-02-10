/***********************************************************************
 * Header File:
 *    Unit tests for King
 ************************************************************************/

#pragma once

 /***************************************************
  * KING TEST
  * Test the King class
  ***************************************************/
class KingTest
{
public:
    void run()
    {
        getMoves_free();
        getMoves_blocked();
        getMoves_capture();
        getMoves_castle_king_moved();
        getMoves_castle_rook_moved();
        getMoves_castle_blocked();
        getMoves_castle();
    };

private:
    void getMoves_free();
    void getMoves_blocked();
    void getMoves_capture();
    void getMoves_castle_king_moved();
    void getMoves_castle_rook_moved();
    void getMoves_castle_blocked();
    void getMoves_castle();

};