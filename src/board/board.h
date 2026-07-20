//
// Created by DENNIS on 6/26/2026.
//

#ifndef SUYA_BOARD_H
#define SUYA_BOARD_H

#include <string>
#include <array>
#include "../utils/utils.h"
#include  "../movegen/Move.h"

const int W = 0;
const int B = 8;
const int EMPTY = 0;
const int PAWN = 1; // 1
const int KNIGHT = 2; // 3
const int BISHOP = 3; // 4
const int ROOK = 4; // 5
const int QUEEN = 5; // 9
const int KING = 6; // 10

const char pieceTypeStringTable[7] = {
  ' ', 'P', 'N', 'B', 'R', 'Q', 'K'
};

/**
 * This Class represents the board as an 8x8 array.
 * [0][0] corresponds to a1
 */

class Board {
public:
  std::array<std::array<int, 8>, 8> squares = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
  };
  bool whiteToMove = true;

  //k for king side q for queen side b for both - for none
  char whiteCanCastle = '-';
  char blackCanCastle = '-';
  // it's an int hence n = 8i+j
  int enpassantSquare = 0;

  int getSquare(int) const;

  int getSquare(int, int) const;

  bool isEmpty(int) const;

  bool isEmpty(int, int) const;

  std::string toString();

  std::array<int, 8> getFile(int) const;

  std::array<int, 8> getRank(int) const;

  int getClosestPieceOnRank(int r, int startingPoint, int dir) const;

  int getClosestPieceOnFile(int f, int startingPoint, int dir) const;

  int getClosestPieceOnDiagonal(int p, int diagonalDirection, int dir) const;

  int getClosestPieceOnDiagonal(int i, int j, int diagonalDirection, int dir) const;

  bool isKingInCheck(int color) const;

  bool isSquareAttacked(int attackingColor, int p) const;

  //only for all moves except castling
  bool isMoveLegal(Move m);

  void applyMove(Move move);

  Board copyAndApplyMove(Move move) const;

  bool checkCanCastleKingSide(int color) const;

  bool checkCanCastleQueenSide(int color) const;
};

#endif //SUYA_BOARD_H
