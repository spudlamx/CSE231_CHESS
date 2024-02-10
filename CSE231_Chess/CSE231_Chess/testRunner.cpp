
/***********************************************************************
 * Source File:
 *    Test Runner 
 ************************************************************************/

#include "testRunner.h"		// for RunTest 
#include "testMove.h"	// for MOVE_TEST
#include "testPosition.h"	// for POSITION_TEST 
#include "testPawn.h" // for PAWN_TEST
#include "testKing.h"     // for KING_TEST
#include <cassert>    
#include "iostream"// for ASSERT
using namespace std;

void RunTest::run()
{
	MoveTest move;
	move.run();
    cout << "Move Tests Pass." << endl;

	PositionTest position;
	position.run();
    cout << "Position Tests Pass." << endl;

	PawnTest pawn;
	pawn.run();
    cout << "Pawn Tests Pass." << endl;

	KingTest king;
	king.run();
    cout << "King Tests Pass." << endl;
    
    cout << "All Tests Pass" << endl;
};
