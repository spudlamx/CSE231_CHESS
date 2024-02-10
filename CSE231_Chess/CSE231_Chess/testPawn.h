/***********************************************************************
 * Header File:
 *    Unit tests for Pawn
 ************************************************************************/

#pragma once


 /***************************************************
  * PAWN TEST
  * Test the Pawn class
  ***************************************************/
class PawnTest
{
public:
    void run()
    { 
        getMoves_blocked();
        getMoves_simple();
        getMoves_initial();
        getMoves_capture();
        getMoves_enpassant();
        getMoves_promotion();
    }

private:
    void getMoves_blocked();
    void getMoves_simple();
    void getMoves_initial();
    void getMoves_capture();
    void getMoves_enpassant();
    void getMoves_promotion();
};
