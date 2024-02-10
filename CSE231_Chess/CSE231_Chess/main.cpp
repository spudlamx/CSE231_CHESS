#include "uiInteract.h"   // for Interface
#include "uiDraw.h"      // for draw*
#include "board.h"        // Include the header file for your Board class
#include "piece.h"
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include "iostream"
#include "testRunner.h"
using namespace std;

// Code with Board object in callback

Board* callBack(Interface* pUI, Board* board) {
    // Step 1: Get positions and pointers
    Position posHover = pUI->getHoverPosition();
    Position posSelect = pUI->getSelectPosition();
    Position posPrevious = pUI->getPreviousPosition();
    Piece* piecePtr = &(*board)[posPrevious];
    Piece* destPtr = &(*board)[posSelect];

    // Step 2: Check if a mouse click has occurred
    if (destPtr->isWhite() != board->isWhiteTurn() && posPrevious == nullptr){
        pUI->clearSelectPosition();
    }
    Move move;
    move.setSrc(posPrevious);
    move.setDes(posSelect);
    move.setCapture(move.pieceTypeFromLetter(destPtr->getLetter()));
    move.setWhiteMove(board->getCurrentMove() % 2 == 0);
    
    // Step 3: Check and handle pawn promotion
    if (piecePtr->getLetter() == 'p') {
        if( posSelect.getRow() == (piecePtr->isWhite() ? 7 : 0)){
            move.setPromote(QUEEN);
        }
        else if (piecePtr->getPosition().getRow() == (piecePtr->isWhite()? 4:3)
                 && destPtr->getPosition().getCol() != piecePtr->getPosition().getCol()
                 && destPtr->getLetter() == ' '
                 && destPtr->getPosition().getRow() == (piecePtr->isWhite()? 5:2)){
            move.setEnPassant();
        }
    }
    if(piecePtr->getLetter() == 'k' && !piecePtr->isMoved()
       && move.getDes().getRow() == posPrevious.getRow()
       && (move.getDes().getCol() == 2||6) ){
        move.setCastle(posSelect.getCol() == 6);
    }

    // Step 4: Check if a valid move has been made
    set<Move> validMoves = piecePtr->getMoves(*board);
    if (posPrevious.isValid()) {  // Check if a piece is selected
        cout << "Move: "<< move.getText() << "\nPossible Moves:\n";
        auto it = validMoves.begin();
        while (it != validMoves.end()) {
            cout << it->getText() << endl;
            if (move.getText() == it->getText()) {
                // Step 5: Make the move and update piece's move count
                piecePtr->setLastMove(board->getCurrentMove());
                board->move(move);
                pUI->clearSelectPosition();
            } else if(piecePtr->isWhite() != destPtr->isWhite() || (*board)[posSelect].getLetter() == ' '){
                pUI->clearSelectPosition();
            }
            ++it;
        }

        // Step 6: Clear the selected position after the move is made
        
    }

    // Step 7: Display the board
    board->display(posHover, posSelect);

    // Step 8: Return the updated board
    return board;
}





int main() {
    Interface ui("Chess");

    // Step 1: Add Classes and Run Unit Tests
    // (Assuming your classes are implemented in separate source files)
    // Run unit tests for key classes
    // ...

    // Step 2: Remove Procedural Chess Code
    // (Remove character-array chess board, getPossibleMoves(), and draw())
    // ...
    RunTest testRunner;
    testRunner.run();
    // Step 3: Use Board Object in Callback
    Board board(&ui); // Assuming Board constructor takes an Interface and a boolean
    ui.run(callBack, &board);

    // Proceed to the next step
}

