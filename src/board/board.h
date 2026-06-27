//
// Created by DENNIS on 6/26/2026.
//

#ifndef SUYA_BOARD_H
#define SUYA_BOARD_H

#include <string>

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
  ' ','P', 'N','B', 'R', 'Q', 'K'
};


class Board {
public:
  int squares[8][8] = {
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

  std::string toString();
};

#endif //SUYA_BOARD_H
