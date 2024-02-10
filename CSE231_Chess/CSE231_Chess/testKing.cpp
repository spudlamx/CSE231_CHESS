/***********************************************************************
 * Source File:
 *    King Test : Unit tests for King
 ************************************************************************/

#include "testKing.h" // for KING_TEST
#include "piece.h"     // for KING
#include <cassert>    
#include "board.h" // for ASSERT
#include "iostream"
using namespace std;
extern Interface* ui;

void KingTest::getMoves_free(){
    Board board(ui);
    board.testBoard();

	//white king e5
    King king(4, 4, true); // e5
    board.assign(king, king.getPosition());

	//EXERCISE
	set<Move> moves = king.getMoves(board);
    vector<string> expectedMoves = {"e5d4", "e5e4", "e5f4", "e5d5", "e5f5", "e5d6", "e5e6", "e5f6"};

	//VERIFY
    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }
    
	//TEARDOWN
	board.reset();
};
void KingTest::getMoves_blocked() {
    Board board(ui);
    board.testBoard();


    // White king at e5
    King king(4, 4, true); // e5
    board.assign(king, king.getPosition());

    // White pawns blocking king's moves
    Pawn pawn1(3, 5, true); // f4
    board.assign(pawn1, pawn1.getPosition());

    Pawn pawn2(4, 5, true); // f5
    board.assign(pawn2, pawn2.getPosition());

    Pawn pawn3(5, 5, true); // f6
    board.assign(pawn3, pawn3.getPosition());

    Pawn pawn4(5, 4, true); // e6
    board.assign(pawn4, pawn4.getPosition());

    Pawn pawn5(3, 4, true); // e4
    board.assign(pawn5, pawn5.getPosition());

    Pawn pawn6(5, 3, true); // d6
    board.assign(pawn6, pawn6.getPosition());

    Pawn pawn7(4, 3, true); // d5
    board.assign(pawn7, pawn7.getPosition());

    Pawn pawn8(3, 3, true); // d4
    board.assign(pawn8, pawn8.getPosition());

    // EXERCISE
    set<Move> moves = king.getMoves(board);

    // VERIFY
    assert(moves.empty());
    

    // TEARDOWN
    board.reset();
}


void KingTest::getMoves_capture() {
    Board board(ui);
    board.testBoard();


    // White king at e5
    King king(4, 4, true); // e5
    board.assign(king, king.getPosition());

    // Black pawns surrounding king
    Pawn pawn1(3, 5, false); // f4
    board.assign(pawn1, pawn1.getPosition());

    Pawn pawn2(4, 5, false); // f5
    board.assign(pawn2, pawn2.getPosition());

    Pawn pawn3(5, 5, false); // f6
    board.assign(pawn3, pawn3.getPosition());

    Pawn pawn4(5, 4, false); // e6
    board.assign(pawn4, pawn4.getPosition());

    Pawn pawn5(3, 4, false); // e4
    board.assign(pawn5, pawn5.getPosition());

    Pawn pawn6(5, 3, false); // d6
    board.assign(pawn6, pawn6.getPosition());

    Pawn pawn7(4, 3, false); // d5
    board.assign(pawn7, pawn7.getPosition());

    Pawn pawn8(3, 3, false); // d4
    board.assign(pawn8, pawn8.getPosition());


    //EXERCISE
    set<Move> moves = king.getMoves(board);
    vector<string> expectedMoves = {"e5d4p", "e5e4p", "e5f4p", "e5d5p", "e5f5p", "e5d6p", "e5e6p", "e5f6p"};

    //VERIFY
    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }
    // TEARDOWN
    board.reset();
}

void KingTest::getMoves_castle_king_moved() {
    Board board(ui);
    board.testBoard();

    // White king at e1
    King king(0, 4, true); // e1
    king.setNMoves(1); // King moved once
    board.assign(king, king.getPosition());

    // White pawns
    Pawn pawn1(1, 3, true); // d2
    board.assign(pawn1, pawn1.getPosition());

    Pawn pawn2(1, 4, true); // e2
    board.assign(pawn2, pawn2.getPosition());

    Pawn pawn3(1, 5, true); // f2
    board.assign(pawn3, pawn3.getPosition());

    // White rooks
    Rook rook1(0, 0, true); // a1
    board.assign(rook1, rook1.getPosition());

    Rook rook2(0, 7, true); // h1
    board.assign(rook2, rook2.getPosition());

    // EXERCISE
    set<Move> moves = king.getMoves(board);

    // VERIFY
    vector<string> expectedMoves = { "e1d1", "e1f1" };

    assert(moves.size() == expectedMoves.size());

    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }

    // TEARDOWN
    board.reset();
}




void KingTest::getMoves_castle_rook_moved() {
    Board board(ui);
    board.testBoard();

    // White king at e1
    King king(0, 4, true); // e1
    board.assign(king, king.getPosition());

    // White pawns
    Pawn pawn1(1, 3, true); // d2
    board.assign(pawn1, pawn1.getPosition());

    Pawn pawn2(1, 4, true); // e2
    board.assign(pawn2, pawn2.getPosition());

    Pawn pawn3(1, 5, true); // f2
    board.assign(pawn3, pawn3.getPosition());

    // White rooks
    Rook rook1(0, 0, true); // a1
    rook1.setNMoves(1); // King moved once
    board.assign(rook1, rook1.getPosition());

    Rook rook2(0, 7, true); // h1
    rook2.setNMoves(1); // King moved once
    board.assign(rook2, rook2.getPosition());

    // EXERCISE
    set<Move> moves = king.getMoves(board);

    // VERIFY
    vector<string> expectedMoves = { "e1d1", "e1f1" };

     assert(moves.size() == expectedMoves.size());

    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }

    // TEARDOWN
    board.reset();
}


void KingTest::getMoves_castle_blocked() {
    Board board(ui);
    board.testBoard();

    // White king at e1
    King king(0, 4, true); // e1
    board.assign(king, king.getPosition());

    // White pawns
    Pawn pawn1(1, 3, true); // d2
    board.assign(pawn1, pawn1.getPosition());

    Pawn pawn2(1, 4, true); // e2
    board.assign(pawn2, pawn2.getPosition());

    Pawn pawn3(1, 5, true); // f2
    board.assign(pawn3, pawn3.getPosition());

    // White pawns blocking castling
    Pawn pawn4(0, 1, true); // b1
    board.assign(pawn4, pawn4.getPosition());

    Pawn pawn5(0, 6, true); // g1
    board.assign(pawn5, pawn5.getPosition());

    // White rooks
    Rook rook1(0, 0, true); // a1
    board.assign(rook1, rook1.getPosition());

    Rook rook2(0, 7, true); // h1
    board.assign(rook2, rook2.getPosition());

    // EXERCISE
    set<Move> moves = king.getMoves(board);

    // VERIFY
    vector<string> expectedMoves = { "e1d1", "e1f1" };

//    assert(moves.size() == expectedMoves.size());

    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }

    // TEARDOWN
    board.reset();
}



void KingTest::getMoves_castle() {
    Board board(ui);
    board.testBoard();

    // White king at e1
    King king(0, 4, true); // e1
    board.assign(king, king.getPosition());

    // White pawns
    Pawn pawn1(1, 3, true); // d2
    board.assign(pawn1, pawn1.getPosition());

    Pawn pawn2(1, 4, true); // e2
    board.assign(pawn2, pawn2.getPosition());

    Pawn pawn3(1, 5, true); // f2
    board.assign(pawn3, pawn3.getPosition());

    // White rooks
    Rook rook1(0, 0, true); // a1
    board.assign(rook1, rook1.getPosition());

    Rook rook2(0, 7, true); // h1
    board.assign(rook2, rook2.getPosition());

    // EXERCISE
    set<Move> moves = king.getMoves(board);

    // VERIFY
    vector<string> expectedMoves = { "e1c1C", "e1d1", "e1f1", "e1g1c" };

    assert(moves.size() == expectedMoves.size());

    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }

    // TEARDOWN
    board.reset();
}
