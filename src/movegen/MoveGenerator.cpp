//
// Created by DENNIS on 6/27/2026.
//


#include "MoveGenerator.h"

#include "../utils/utils.h"

std::list<Move> generateMoves(const Board &b) {
  std::list<Move> moveList;
  int workingColor = b.whiteToMove ? W : B;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      const int piece = b.squares[i][j];
      const int type = pieceType(piece);
      const int color = pieceColor(piece);

      if (color != workingColor) {
        continue;
      }

      //pawn movement
      if (type == PAWN) {
        int pawnPush = 8 * i + j + 8;

        //if the pawn isnt on the last rank and the square is not occupied by friendly piece
        if (withinBoard(pawnPush) && isEmpty(b.getSquare(pawnPush))) {
          Move push{.start = 8 * i + j, .target = pawnPush, .piece = piece};
          moveList.push_back(push);
        }

        int leftCaptureSquare = 8 * i + j + 7;
        int rightCaptureSquare = 8 * i + j + 9;
      }
    }
  }
  return moveList;
}
