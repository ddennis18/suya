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
    12, 10, 11, 13, 14, 11, 10, 12,
    9, 9, 9, 9, 9, 9, 9, 9,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    4, 2, 3, 5, 6, 3, 2, 4,
  };
  bool whiteToMove = true;
  bool whiteCanCastle = false;
  bool blackCanCastle = false;

  std::string toString();
};

#endif //SUYA_BOARD_H
