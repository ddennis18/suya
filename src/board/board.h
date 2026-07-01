//
// Created by DENNIS on 6/26/2026.
//

#ifndef SUYA_BOARD_H
#define SUYA_BOARD_H

#include <string>
#include <array>
#include "../utils/utils.h"

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

/**NOTE: 0,0 corresponds to a1
 * as a consequence the board is in black's perspective
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

  std::array<int, 8> getSquaresOnDiagonal(int i, int j, int dir);
};

#endif //SUYA_BOARD_H
