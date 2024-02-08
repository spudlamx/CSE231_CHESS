/***********************************************************************
 * Source File:
 *    Pawn Test : Unit tests for Pawn
 ************************************************************************/
#include "iostream"
#include "testPawn.h" // for PAWN_TEST
#include "board.h"	// for BOARD
#include <cassert>        // for ASSERT
#include <set>
// In your header file (e.g., PawnTest.h)
extern ogstream* pgout;


void PawnTest::getMoves_blocked()
{
    // SETUP
    bool testB = true;
    Board board(pgout);


    // White pawn at d4, black pawn at d5
    Pawn pawn1(3, 3, testB);
 

    board.assign(pawn1, pawn1.getPosition());
    
    // Black color pawn at the same column (d5)
    Pawn pawn2(4, 3, false);
    board.assign(pawn2, pawn2.getPosition());

    // EXERCISE
    set<Move> moves = pawn1.getMoves(board);
    
    // VERIFY
    assert(moves.size() == 0);

    // TEARDOWN
    board.reset();
//    cout << "getMoves_blocked passed" << endl;
}




void PawnTest::getMoves_simple()
{
    //SETUP
    Board board(pgout);

    //white pawn b4
    Pawn pawn(3, 1, true);
    board.assign(pawn, pawn.getPosition());

    //EXERCISE
    set<Move> moves = pawn.getMoves(board);

    // VERIFY

    vector<string> expectedMoves = {"b4b5"};

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
//    cout << "getMoves_simple passed" << endl;

}




void PawnTest::getMoves_initial()
{
	//SETUP
    Board board(pgout);

	//white pawn b2
    Pawn pawn(1, 1, true);
    board.assign(pawn, pawn.getPosition());


	//EXERCISE
    set<Move> moves = pawn.getMoves(board);
    vector<string> expectedMoves = {"b2b3","b2b4"};

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
//    cout << "getMoves_initial passed" << endl;

}

void PawnTest::getMoves_capture()
{
	//SETUP
    Board board(pgout);
    board.testBoard();

	//white pawn b6
	Pawn pawn(5, 1, true);
    board.assign(pawn, pawn.getPosition());

	//black pawn a7, b7, c7
	Pawn pawn2(6, 0, false);
    board.assign(pawn2, pawn2.getPosition());

    Pawn pawn3(6, 1, false);
    board.assign(pawn3, pawn3.getPosition());

    Pawn pawn4(6, 2, false);
    board.assign(pawn4, pawn4.getPosition());


	//EXERCISE
    set<Move> moves = pawn.getMoves(board);
    vector<string> expectedMoves = {"b6a7p", "b6c7p"};

    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }
	//VERIFY
//	assert(stringMoves == {"b6a7p","b6c7p"});

	//TEARDOWN
	board.reset();
//    cout << "getMoves_capture passed" << endl;

}

void PawnTest::getMoves_enpassant()
{
	//SETUP
    Board board(pgout);

	//white pawn b5
    Pawn pawn(4, 1, true);
    board.assign(pawn, pawn.getPosition());
	
	//black pawn b6
    Pawn pawn2(5, 1, false);
    board.assign(pawn2, pawn2.getPosition());
    
	//black pawn a6, c6 lastmove = 1
    Pawn pawn3(4, 0, false);
    pawn3.setNMoves(1);
    board.assign(pawn3, pawn3.getPosition());
    
    Pawn pawn4(4, 2, false);
    pawn4.setNMoves(1);
    board.assign(pawn4, pawn4.getPosition());
    board[pawn4.getPosition()].setNMoves(1);
	//EXERCISE
    set<Move> moves = pawn.getMoves(board);
    vector<string> expectedMoves = {"b5a6E", "b5c6E"};

    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }
	//VERIFY
//	assert(moves == {"b5c6E","b5a6E"});

	//TEARDOWN
	board.reset();
//    cout << "getMoves_enpassant passed" << endl;

}

void PawnTest::getMoves_promotion()
{
	//SETUP
    Board board(pgout);

	//white pawn b7
    Pawn pawn(6, 1, true);
    board.assign(pawn, pawn.getPosition());
    Space space(7, 1);
    board.assign(space, {space.getPosition()}); //b7
    board.assign(space, {7, 0});
    board.assign(space, {7, 2});
	//EXERCISE
    set<Move> moves = pawn.getMoves(board);
    vector<string> expectedMoves = {"b7b8Q"};

    auto it = moves.begin();
    auto expectedIt = expectedMoves.begin();

    while (it != moves.end()) {
//        cout << it->getText() << " || " << *expectedIt << endl;
        assert(it->getText() == *expectedIt);
        ++it;
        ++expectedIt;
    }
    assert(moves.size() == expectedMoves.size());
	//VERIFY
//	assert(moves == {"b7b8Q"});

	//TEARDOWN
	board.reset();
//    cout << "getMoves_promotion passed" << endl;

}


