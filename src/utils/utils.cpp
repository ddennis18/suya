#include "utils.h"

bool withinBoard(const int n) {
  return (0 <= n) && (n < 64);
}

bool withinBoard(const int i, const int j) {
  return (0 <= i) && (i < 8) && (0 <= j) && (j < 8);
}

int pieceType(int p) {
  return p & 0b0111;
}

int pieceColor(int p) {
  return p & 0b1000;
}

bool isEmpty(int p) {
  return (p == 0);
}

std::tuple<int, int> indexToCoordinates(const int i) {
  return {(i - i % 8) / 8, i % 8};
}

int getSquareColor(int p) {
  auto [i, j] = indexToCoordinates(p);
  return (i + j) % 2 == 0 ? B : W;
}

int getSquareColor(int i, int j) {
  std::array<int, 8> getDiagonal(int p);
  return (i + j) % 2 == 0 ? B : W;
}

std::array<int, 8> getSquaresOnDiagonal(int i, int j, int dir) {
  std::array<int, 8> diagonal = {-1, -1, -1, -1, -1, -1, -1, -1};
  int k = 0;
  int x = i;
  int y = j;
  int jdir = dir == -1 ? -dir : dir;

  while (withinBoard(x, y)) {
    diagonal[k] = 8 * x + y;
    k++;
    x += dir;
    y += jdir;
  }

  x = i - dir;
  y = j - jdir;

  while (withinBoard(x, y)) {
    diagonal[k] = 8 * x + y;
    x -= dir;
    y -= jdir;
    k++;
  }

  return diagonal;
}
