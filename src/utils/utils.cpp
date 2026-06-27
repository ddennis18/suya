#include "utils.h"

bool withinBoard(const int n) {
  return (0 <= n) && (n < 64);
}


int pieceType(int p) {
  return p & 0b0111;
}

int pieceColor(int p) {
  return p & 0b1000;
}

bool isEmpty(int p) {
  return (p ==0);
}

std::tuple<int, int> indexToCoordinates(const int i) {
  return {(i - i % 8) / 8, i % 8};
}
