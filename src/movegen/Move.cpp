//
// Created by DENNIS on 7/14/2026.
//

#include "Move.h"

void MoveList::add(const Move &m) {
  list[count++] = m;
}

int MoveList::lenght() const {
  return count;
}

Move MoveList::operator[](int index) const {
  return list[index];
}
