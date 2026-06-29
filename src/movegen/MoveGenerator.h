//
// Created by DENNIS on 6/27/2026.
//

#ifndef SUYA_MOVE_H
#define SUYA_MOVE_H

#include <list>

#include "../board/board.h"

const int MAX_MOVES_PER_POSITION = 256;

class Move {
public:
  int start = 0;
  int target = 0;
  int piece = 0; //empty
  bool captures = false;
  int capturedPiece = 0; //empty;
};

class MoveList {
private:
  int count = 0;

public:
  Move list[MAX_MOVES_PER_POSITION];

  void add(const Move &);

  int lenght() const;
};

MoveList generateMoves(const Board &);

#endif //SUYA_MOVE_H
