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

int Board::getClosestPieceOnDiagonal(int p, int diagonalDirection, int dir) const {
  auto [i,j] = indexToCoordinates(p);
  return getClosestPieceOnDiagonal(i, j, diagonalDirection, dir);
}

int Board::getClosestPieceOnDiagonal(int i, int j, int diagonalDirection, int dir) const {
  auto diagonal = getSquaresOnDiagonal(i, j, diagonalDirection);
  int di = 1;
  while (diagonal[di] != -1 && di < 8) {
    const int ds = diagonal[di];
    if (!isEmpty(ds) && dir * ds > dir * (8 * i + j)) {
      return ds;
    }
    di++;
  }

  return -1;
}

bool Board::isKingInCheck(int color) const {
  //find the king
  int p = 0;
  for (; p < 64; p++) {
    if (const int piece = getSquare(p);
      pieceColor(piece) == color && pieceType(piece) == KING) {
      break;
    }
  }
  auto [i,j] = indexToCoordinates(p);

  //Attack On the Rank By Rook and Queen
  int rightAttacker = getClosestPieceOnRank(i, j, +1);
  if (rightAttacker != -1) {
    int a = getSquare(8 * i + rightAttacker);
    if (pieceColor(a) != color && (pieceType(a) == ROOK || pieceColor(a) == QUEEN)) {
      return true;
    }
  }
  int leftAttacker = getClosestPieceOnRank(i, j, -1);
  if (leftAttacker != -1) {
    int a = getSquare(8 * i + leftAttacker);
    if (pieceColor(a) != color && (pieceType(a) == ROOK || pieceColor(a) == QUEEN)) {
      return true;
    }
  }

  //Attack On the file By Rook and Queen
  int topAttacker = getClosestPieceOnFile(j, i, +1);
  if (topAttacker != -1) {
    int a = getSquare(8 * topAttacker + j);
    if (pieceColor(a) != color && (pieceType(a) == ROOK || pieceColor(a) == QUEEN)) {
      return true;
    }
  }

  int bottomAttacker = getClosestPieceOnFile(j, i, -1);
  if (bottomAttacker != -1) {
    int a = getSquare(8 * bottomAttacker + j);
    if (pieceColor(a) != color && (pieceType(a) == ROOK || pieceColor(a) == QUEEN)) {
      return true;
    }
  }

  int topRightDiagonalAttacker = getClosestPieceOnDiagonal(p, +1, +1);
  if (topRightDiagonalAttacker != -1) {
    int a = getSquare(topRightDiagonalAttacker);
    if (pieceColor(a) != color && (pieceType(a) == BISHOP || pieceColor(a) == QUEEN)) {
      return true;
    }
  }

  int bottomLeftDiagonalAttacker = getClosestPieceOnDiagonal(p, +1, -1);
  if (bottomLeftDiagonalAttacker != -1) {
    int a = getSquare(bottomLeftDiagonalAttacker);
    if (pieceColor(a) != color && (pieceType(a) == BISHOP || pieceColor(a) == QUEEN)) {
      return true;
    }
  }

  int topLeftDiagonalAttacker = getClosestPieceOnDiagonal(p, -1, +1);
  if (topLeftDiagonalAttacker != -1) {
    int a = getSquare(topLeftDiagonalAttacker);
    if (pieceColor(a) != color && (pieceType(a) == BISHOP || pieceColor(a) == QUEEN)) {
      return true;
    }
  }

  int bottomRightDiagonalAttacker = getClosestPieceOnDiagonal(p, -1, -1);
  if (bottomRightDiagonalAttacker != -1) {
    int a = getSquare(bottomRightDiagonalAttacker);
    if (pieceColor(a) != color && (pieceType(a) == BISHOP || pieceColor(a) == QUEEN)) {
      return true;
    }
  }

  std::array<std::array<int, 2>, 8> relativeSquares = {
    2, 1,
    2, -1,
    1, 2,
    -1, 2,
    1, -2,
    -1, -2,
    -2, 1,
    -2, -1
  };

  for (auto rs: relativeSquares) {
    rs[0] += i;
    rs[1] += j;
    if (!withinBoard(rs[0], rs[1])) {
      continue;
    }
    int a = getSquare(rs[0], rs[1]);
    if (pieceColor(a) != color && pieceType(a) == KNIGHT) {
      return true;
    }
  }

  int dir = color == W ? +1 : -1;
  int frontLeftSquare = getSquare(i + dir, j + 1);
  int frontRightSquare = getSquare(i + dir, j - 1);
  if (pieceColor(frontLeftSquare) != color && pieceType(frontLeftSquare) == PAWN) {
    return true;
  }
  if (pieceColor(frontRightSquare) != color && pieceType(frontRightSquare) == PAWN) {
    return true;
  }

  return false;
}

bool Board::applyMove(Move move) {
  int dir = pieceColor(move.piece) == W ? +1 : -1;
  auto [si, sj] = indexToCoordinates(move.start);
  auto [ti, tj] = indexToCoordinates(move.target);

  squares[si][sj] = EMPTY;
  squares[ti][tj] = move.piece;

  if (move.isEnpassant) {
    squares[ti - dir][tj] = EMPTY;
  }

  if (move.isCastling) {
    bool isKingSide = tj - sj > 0;
    if (isKingSide) {
      squares[si][7] = EMPTY;
      squares[si][5] = pieceColor(move.piece) | ROOK;
    } else {
      squares[si][0] = EMPTY;
      squares[si][3] = pieceColor(move.piece) | ROOK;
    }
  }

  whiteToMove = !whiteToMove;

  return true;
}

bool Board::checkCanCastleKingSide(int color) const {
  if (color == W) {
    if (whiteCanCastle == 'q' || whiteCanCastle == '-') {
      return false;
    }
  }
  if (color == B) {
    if (blackCanCastle == 'q' || blackCanCastle == '-') {
      return false;
    }
  }
  int i = color == W ? 0 : 7;

  if (isEmpty(i, 5) && isEmpty(i, 6) && getSquare(i, 7) == (color | ROOK)) {
    return true;
  }

  return false;
}

bool Board::checkCanCastleQueenSide(int color) const {
  if (color == W) {
    if (whiteCanCastle == 'k' || whiteCanCastle == '-') {
      return false;
    }
  }
  if (color == B) {
    if (blackCanCastle == 'k' || blackCanCastle == '-') {
      return false;
    }
  }
  int i = color == W ? 0 : 7;

  if (isEmpty(i, 1) && isEmpty(i, 2) && isEmpty(i, 3) && getSquare(i, 7) == (color | ROOK)) {
    return true;
  }

  return false;
}
