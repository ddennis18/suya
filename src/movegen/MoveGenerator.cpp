//
// Created by DENNIS on 6/27/2026.
//


#include "MoveGenerator.h"

#include "../utils/utils.h"

std::list<Move> generateMoves(const Board &b) {
  std::list<Move> moveList;
  int workingColor = b.whiteToMove ? W : B;

  //+ve for white and negative for black tells up where is forward from each perspective
  int direction = (workingColor == W) ? +1 : -1;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      const int piece = b.squares[i][j];
      if (piece == EMPTY) {
        continue;
      }
      const int type = pieceType(piece);
      const int color = pieceColor(piece);

      if (color != workingColor) {
        continue;
      }

      //pawn movement
      if (type == PAWN) {
        int pawnPush = 8 * i + j + direction * 8;
        //if the pawn isnt on the last rank and the square is not occupied by friendly piece
        if (withinBoard(pawnPush) && b.isEmpty(pawnPush)) {
          Move push{.start = 8 * i + j, .target = pawnPush, .piece = piece};
          moveList.push_back(push);
        }

        int doublePawnPush = 8 * i + j + direction * 16;
        bool inStartingSquare = ((workingColor == W) && (i == 1)) || ((workingColor == B) && (i == 6));
        if (inStartingSquare && b.isEmpty(pawnPush) && b.isEmpty(doublePawnPush)) {
          Move push{.start = 8 * i + j, .target = doublePawnPush, .piece = piece};
          moveList.push_back(push);
        }

        //NOTE: THE Board is in black's perspective
        int leftCapture = 8 * i + j + direction * 7;
        int rightCapture = 8 * i + j + direction * 9;

        //j!=0 for the a file since it cant capture to the left whilst on the a file
        if ((j != 7) && withinBoard(leftCapture) && !b.isEmpty(leftCapture) &&
            (pieceColor(b.getSquare(leftCapture)) != workingColor)) {
          int capturedPiece = b.getSquare(leftCapture);
          Move m{
            .start = 8 * i + j, .target = leftCapture,
            .piece = piece, .captures = true, .capturedPiece = capturedPiece
          };

          moveList.push_back(m);
        }

        //j!=7 for the h file since it cant capture to the right whilst on the h file
        if ((j != 0) && withinBoard(rightCapture) && !b.isEmpty(rightCapture) &&
            (pieceColor(b.getSquare(rightCapture)) != workingColor)) {
          int capturedPiece = b.getSquare(rightCapture);
          Move m{
            .start = 8 * i + j, .target = rightCapture,
            .piece = piece, .captures = true, .capturedPiece = capturedPiece
          };

          moveList.push_back(m);
        }
      }
    }
  }
  return moveList;
}
