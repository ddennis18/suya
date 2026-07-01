//
// Created by DENNIS on 6/26/2026.
//

#include "board.h"

#include <algorithm>

std::string Board::toString() {
  std::string ret = "\n";
  for (int i = 7; i >= 0; i--) {
    for (int j = 7; j >= 0; j--) {
      int p = squares[i][j];
      const int color = p & 0b1000;
      const int type = p & 0b0111;

      char ps = pieceTypeStringTable[type];
      if (color == B) {
        ps = std::tolower(ps);
      };
      ret += '|';
      ret += ps;
    }
    ret += "|\n";
  }
  return ret;
}

int Board::getSquare(const int n) const {
  auto [i,j] = indexToCoordinates(n);
  return squares[i][j];
}

int Board::getSquare(const int i, const int j) const {
  return squares[i][j];
}

bool Board::isEmpty(const int n) const {
  auto [i, j] = indexToCoordinates(n);
  return (squares[i][j] == EMPTY);
}

bool Board::isEmpty(const int i, const int j) const {
  return withinBoard(i, j) && (squares[i][j] == EMPTY);
}

std::array<int, 8> Board::getFile(int f) const {
  std::array<int, 8> file;
  for (int i = 0; i < 8; i++) {
    file[i] = squares[i][f];
  }

  return file;
}

std::array<int, 8> Board::getRank(int rank) const {
  return squares[rank];
}

int Board::getClosestPieceOnRank(int r, int startingPoint, int dir) const {
  auto rank = getRank(r);
  startingPoint += dir;
  for (; withinBoard(r, startingPoint) && isEmpty(r, startingPoint);
         startingPoint += dir) {
    continue;
  }
  if (!withinBoard(r, startingPoint)) {
    //at a corner so there's nothing there in that direction
    return -1;
  }

  return startingPoint;
}

int Board::getClosestPieceOnFile(int f, int startingPoint, int dir) const {
  auto file = getFile(f);
  startingPoint += dir;
  for (; withinBoard(startingPoint, f) && isEmpty(startingPoint, f);
         startingPoint += dir) {
    continue;
  }
  if (!withinBoard(startingPoint, f)) {
    //at a corner so there's nothing there in that direction
    return -1;
  }

  return startingPoint;
}

std::array<int, 8> Board::getSquaresOnDiagonal(int i, int j, int dir) {
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
