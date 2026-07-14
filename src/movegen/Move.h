//
// Created by DENNIS on 7/14/2026.
//

#ifndef SUYA_MOVE_H
#define SUYA_MOVE_H

const int MAX_MOVES_PER_POSITION = 256;

class Move {
public:
  int start = 0;
  int target = 0;
  int piece = 0; //empty
  bool captures = false;
  int capturedPiece = 0; //empty;
  bool isEnpassant = false;
};

class MoveList {
private:
  int count = 0;

public:
  Move list[MAX_MOVES_PER_POSITION];

  void add(const Move &);

  int lenght() const;

  //WARNING: this does not check if the index is greater than count
  Move operator[](int) const;
};

#endif //SUYA_MOVE_H
