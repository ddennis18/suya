//
// Created by DENNIS on 6/27/2026.
//

#ifndef SUYA_MOVE_H
#define SUYA_MOVE_H

#include <list>

#include "../board/board.h"

struct Move {
public:
  int start = 0;
  int target = 0;
  int piece = 0; //empty
  bool captures = false;
  int capturedPiece = 0; //empty;
};

std::list<Move> generateMoves(Board);

#endif //SUYA_MOVE_H
