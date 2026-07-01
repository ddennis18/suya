//
// Created by DENNIS on 6/27/2026.
//


#include "MoveGenerator.h"

#include <ios>

#include "../utils/utils.h"

void MoveList::add(const Move &m) {
  list[count++] = m;
}

int MoveList::lenght() const {
  return count;
}

Move MoveList::operator[](int index) const {
  return list[index];
}

MoveList generateMoves(const Board &b) {
  MoveList moveList;
  int workingColor = b.whiteToMove ? W : B;

  //+ve for white and negative for black tells up where is forward from each perspective
  int direction = (workingColor == W) ? +1 : -1;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      const int piece = b.squares[i][j];
      if (piece == EMPTY) {
        continue;
      }
      const int type = pieceType(piece);
      const int color = pieceColor(piece);

      if (color != workingColor) {
        continue;
      }

      //pawn movement
      if (type == PAWN) {
        int pawnPush = 8 * i + j + direction * 8;
        //if the pawn isnt on the last rank and the square is not occupied by friendly piece
        if (withinBoard(pawnPush) && b.isEmpty(pawnPush)) {
          Move push{.start = 8 * i + j, .target = pawnPush, .piece = piece};
          moveList.add(push);
        }

        int doublePawnPush = 8 * i + j + direction * 16;
        bool inStartingSquare = ((workingColor == W) && (i == 1)) || ((workingColor == B) && (i == 6));
        if (inStartingSquare && b.isEmpty(pawnPush) && b.isEmpty(doublePawnPush)) {
          Move push{.start = 8 * i + j, .target = doublePawnPush, .piece = piece};
          moveList.add(push);
        }

        //NOTE: THE Board is in black's perspective
        int leftCapture = 8 * i + j + direction * 7;
        int rightCapture = 8 * i + j + direction * 9;

        //j!=7 for the a file since it cant capture to the left whilst on the a file
        if ((j != 7) && withinBoard(leftCapture) && !b.isEmpty(leftCapture) &&
            (pieceColor(b.getSquare(leftCapture)) != workingColor)
            && (pieceType(b.getSquare(leftCapture)) != KING)) {
          int capturedPiece = b.getSquare(leftCapture);
          Move m{
            .start = 8 * i + j, .target = leftCapture,
            .piece = piece, .captures = true, .capturedPiece = capturedPiece
          };

          moveList.add(m);
        }

        //j!=0 for the h file since it cant capture to the right whilst on the h file
        if ((j != 0) && withinBoard(rightCapture) && !b.isEmpty(rightCapture) &&
            (pieceColor(b.getSquare(rightCapture)) != workingColor)
            && (pieceType(b.getSquare(rightCapture)) != KING)) {
          int capturedPiece = b.getSquare(rightCapture);
          Move m{
            .start = 8 * i + j, .target = rightCapture,
            .piece = piece, .captures = true, .capturedPiece = capturedPiece
          };

          moveList.add(m);
        }
      } else if (type == KNIGHT) {
        //squares the knight can move to relative to its position
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
          int p = rs[0] * 8 + rs[1];

          //skip the square if its outside the board
          //NOTE i didnt use the single number position to check within board because that wraps
          //around the board which i dont want
          if (!withinBoard(rs[0], rs[1])) { continue; }

          int square = b.getSquare(p);
          if (square == EMPTY) {
            Move m = {.start = 8 * i + j, .target = p, .piece = piece};
            moveList.add(m);
          } else if ((pieceColor(square) != workingColor) && (pieceType(square) != KING)) {
            Move m = {
              .start = 8 * i + j, .target = p, .piece = piece,
              .captures = true, .capturedPiece = square
            };
            moveList.add(m);
          }
        }
      } else if (type == ROOK) {
        //rank movement
        auto right = b.getClosestPieceOnRank(i, j, +1);
        //no obstruction till the end of the board
        if (right == -1) {
          right = 7;
        }
        auto left = b.getClosestPieceOnRank(i, j, -1);
        if (left == -1) {
          left = 0;
        }

        for (int m = left; m <= right; m++) {
          Move move{.start = 8 * i + j, .target = 8 * i + m, .piece = piece};
          int square = b.getSquare(i, m);
          if (!b.isEmpty(i, m) && pieceColor(square) != workingColor) {
            move.captures = true;
            move.capturedPiece = square;
          } else if (!b.isEmpty(i, m) && pieceColor(square) == workingColor) {
            continue;
          }

          moveList.add(move);
        }

        //file movement
        auto top = b.getClosestPieceOnFile(j, i, -1);
        //no obstruction till the end of the board
        if (top == -1) {
          top = 0;
        }
        auto bottom = b.getClosestPieceOnFile(j, i, +1);
        if (bottom == -1) {
          bottom = 8;
        }

        for (int m = top; m <= bottom; m++) {
          Move move{.start = 8 * i + j, .target = 8 * m + j, .piece = piece};
          int square = b.getSquare(m, j);
          if (!b.isEmpty(m, j) && pieceColor(square) != workingColor) {
            move.captures = true;
            move.capturedPiece = square;
          } else if (!b.isEmpty(m, j) && pieceColor(square) == workingColor) {
            continue;
          }

          moveList.add(move);
        }
      } else if (type == BISHOP) {
        auto squaresOnRightDiagonal = getSquaresOnDiagonal(i, j, +1);
        int topRight = b.getClosestPieceOnDiagonal(i, j, +1, +1);
        if (topRight == -1) {
          topRight = 63;
        }
        int bottomLeft = b.getClosestPieceOnDiagonal(i, j, +1, -1);
        if (bottomLeft == -1) {
          bottomLeft = 0;
        }

        int di = 1;
        while (squaresOnRightDiagonal[di] != -1 && di < 8) {
          //target square
          int ds = squaresOnRightDiagonal[di];
          if (!(bottomLeft <= ds && ds <= topRight)) {
            di++;
            continue;
          }

          int p = b.getSquare(ds);
          Move move{.start = 8 * i + j, .target = ds, .piece = piece};

          if (!b.isEmpty(ds) && pieceColor(p) != workingColor) {
            move.captures = true;
            move.capturedPiece = p;
          } else if (!b.isEmpty(ds) && pieceColor(p) == workingColor) {
            di++;
            continue;
          }

          moveList.add(move);
          di++;
        }

        auto squaresOnLeftDiagonal = getSquaresOnDiagonal(i, j, -1);
        int topLeft = b.getClosestPieceOnDiagonal(i, j, -1, +1);
        if (topLeft == -1) {
          topLeft = 62;
        }
        int bottomRight = b.getClosestPieceOnDiagonal(i, j, -1, -1);
        if (bottomRight == -1) {
          bottomRight = 1;
        }

        di = 1;
        while (squaresOnLeftDiagonal[di] != -1 && di < 8) {
          //target square
          int ds = squaresOnLeftDiagonal[di];
          if (!(bottomRight <= ds && ds <= topLeft)) {
            di++;
            continue;
          }

          int p = b.getSquare(ds);
          Move move{.start = 8 * i + j, .target = ds, .piece = piece};

          if (!b.isEmpty(ds) && pieceColor(p) != workingColor) {
            move.captures = true;
            move.capturedPiece = p;
          } else if (!b.isEmpty(ds) && pieceColor(p) == workingColor) {
            di++;
            continue;
          }

          moveList.add(move);
          di++;
        }
      }
    }
  }
  return moveList;
}
