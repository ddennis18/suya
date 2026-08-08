//
// Created by DENNIS on 6/27/2026.
//


#include "MoveGenerator.h"

#include <ios>

#include "../utils/utils.h"

MoveList generateMoves(Board &b, bool capturesOnly, bool enpassantOnly) {
  MoveList moveList;
  int workingColor = b.whiteToMove ? W : B;

  //+ve for white and negative for black tells up where is forward from each perspective
  int direction = (workingColor == W) ? +1 : -1;

  auto appendMove = [&moveList, &b, capturesOnly, enpassantOnly](Move m) {
    if (b.isMoveLegal(m)) {
      if (enpassantOnly) {
        if (!m.isEnpassant) {
          return;
        }
        moveList.add(m);
        return;
      }
      if (capturesOnly) {
        if (!m.captures) {
          return;
        }
        moveList.add(m);
        return;
      }


      moveList.add(m);
    }
  };

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
          if ((workingColor == W && i == 6) || (workingColor == B && i == 1)) {
            push.isPromotion = true;
            push.promotedTo = QUEEN;
            appendMove(push);
            push.promotedTo = ROOK;
            appendMove(push);
            push.promotedTo = BISHOP;
            appendMove(push);
            push.promotedTo = KNIGHT;
          }
          appendMove(push);
        }

        int doublePawnPush = 8 * i + j + direction * 16;
        bool inStartingSquare = ((workingColor == W) && (i == 1)) || ((workingColor == B) && (i == 6));
        if (inStartingSquare && b.isEmpty(pawnPush) && b.isEmpty(doublePawnPush)) {
          Move push{.start = 8 * i + j, .target = doublePawnPush, .piece = piece};
          appendMove(push);
        }

        //CAPTURES
        int leftCapture = 8 * (i + direction) + (j - 1);
        int rightCapture = 8 * (i + direction) + (j + 1);

        //NOTE: whites left is black right and vice versa
        int leftBoundary = 0;
        int rightBoundary = 7;

        if ((j != leftBoundary) && withinBoard(leftCapture) && !b.isEmpty(leftCapture) &&
            (pieceColor(b.getSquare(leftCapture)) != workingColor)
            && (pieceType(b.getSquare(leftCapture)) != KING)) {
          int capturedPiece = b.getSquare(leftCapture);
          Move m{
            .start = 8 * i + j, .target = leftCapture,
            .piece = piece, .captures = true, .capturedPiece = capturedPiece
          };
          if ((workingColor == W && i == 6) || (workingColor == B && i == 1)) {
            m.isPromotion = true;
            m.promotedTo = QUEEN;
            appendMove(m);
            m.promotedTo = ROOK;
            appendMove(m);
            m.promotedTo = BISHOP;
            appendMove(m);
            m.promotedTo = KNIGHT;
          }
          appendMove(m);
        }

        if ((j != rightBoundary) && withinBoard(rightCapture) && !b.isEmpty(rightCapture) &&
            (pieceColor(b.getSquare(rightCapture)) != workingColor)
            && (pieceType(b.getSquare(rightCapture)) != KING)) {
          int capturedPiece = b.getSquare(rightCapture);
          Move m{
            .start = 8 * i + j, .target = rightCapture,
            .piece = piece, .captures = true, .capturedPiece = capturedPiece
          };
          if ((workingColor == W && i == 6) || (workingColor == B && i == 1)) {
            m.isPromotion = true;
            m.promotedTo = QUEEN;
            appendMove(m);
            m.promotedTo = ROOK;
            appendMove(m);
            m.promotedTo = BISHOP;
            appendMove(m);
            m.promotedTo = KNIGHT;
          }
          appendMove(m);
        }

        //check for enpassant
        if ((b.enpassantSquare != -1) && pawnCanCaptureEnpassant(b.enpassantSquare, 8 * i + j, workingColor)) {
          Move m{
            .start = 8 * i + j, .target = b.enpassantSquare,
            //NB:-(workingColor - 4) + 4 this is inverts the color NOTE: fix this later
            .piece = piece, .captures = true, .capturedPiece = (-(workingColor - 4) + 4) | PAWN,
            .isEnpassant = true
          };

          appendMove(m);
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
            appendMove(m);
          } else if ((pieceColor(square) != workingColor) && (pieceType(square) != KING)) {
            Move m = {
              .start = 8 * i + j, .target = p, .piece = piece,
              .captures = true, .capturedPiece = square
            };
            appendMove(m);
          }
        }
      } else if (type == ROOK) {
        generateRookMoves(b, appendMove, i, j);
      } else if (type == BISHOP) {
        generateBishopMoves(b, appendMove, i, j);
      } else if (type == QUEEN) {
        //QUEEN is basically  bishop and rook combined
        generateRookMoves(b, appendMove, i, j);
        generateBishopMoves(b, appendMove, i, j);
      } else if (type == KING) {
        //squares the king can move to relative to its position
        std::array<std::array<int, 2>, 8> relativeSquares = {
          0, 1,
          0, -1,
          1, 1,
          1, -1,
          1, 0,
          -1, 1,
          -1, 0,
          -1, -1
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
            appendMove(m);
          } else if ((pieceColor(square) != workingColor) && (pieceType(square) != KING)) {
            Move m = {
              .start = 8 * i + j, .target = p, .piece = piece,
              .captures = true, .capturedPiece = square
            };
            appendMove(m);
          }
        }

        //add the move normally not using the lambda function
        if (b.checkCanCastleKingSide(workingColor)) {
          Move m{.start = 8 * i + j, .target = 8 * i + (j + 2), .piece = piece, .isCastling = true};
          moveList.add(m);
        }

        if (b.checkCanCastleQueenSide(workingColor)) {
          Move m{.start = 8 * i + j, .target = 8 * i + (j - 2), .piece = piece, .isCastling = true};
          moveList.add(m);
        }
      }
    }
  }
  return moveList;
}

template<typename Func>
void generateRookMoves(const Board &b, Func appendMove, const int i, const int j) {
  int workingColor = b.whiteToMove ? W : B;
  int piece = b.getSquare(i, j);
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
      if (pieceType(square) == KING) {
        continue;
      }
      move.captures = true;
      move.capturedPiece = square;
    } else if (!b.isEmpty(i, m) && pieceColor(square) == workingColor) {
      continue;
    }

    appendMove(move);
  }

  //file movement
  auto top = b.getClosestPieceOnFile(j, i, -1);
  //no obstruction till the end of the board
  if (top == -1) {
    top = 0;
  }
  auto bottom = b.getClosestPieceOnFile(j, i, +1);
  if (bottom == -1) {
    bottom = 7;
  }

  for (int m = top; m <= bottom; m++) {
    Move move{.start = 8 * i + j, .target = 8 * m + j, .piece = piece};
    int square = b.getSquare(m, j);
    if (!b.isEmpty(m, j) && pieceColor(square) != workingColor) {
      if (pieceType(square) == KING) {
        continue;
      }
      move.captures = true;
      move.capturedPiece = square;
    } else if (!b.isEmpty(m, j) && pieceColor(square) == workingColor) {
      continue;
    }

    appendMove(move);
  }
}

template<typename Func>
void generateBishopMoves(const Board &b, Func appendMove, const int i, const int j) {
  int workingColor = b.whiteToMove ? W : B;
  int piece = b.getSquare(i, j);
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
      if (pieceType(p) == KING) {
        di++;
        continue;
      }
      move.captures = true;
      move.capturedPiece = p;
    } else if (!b.isEmpty(ds) && pieceColor(p) == workingColor) {
      di++;
      continue;
    }

    appendMove(move);
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
      if (pieceType(p) == KING) {
        di++;
        continue;
      }
      move.captures = true;
      move.capturedPiece = p;
    } else if (!b.isEmpty(ds) && pieceColor(p) == workingColor) {
      di++;
      continue;
    }

    appendMove(move);
    di++;
  }
}

bool pawnCanCaptureEnpassant(int enpassantSquare, int pawnSquare, int color) {
  if (enpassantSquare == -1) return false;
  auto [ei, ej] = indexToCoordinates(enpassantSquare);
  auto [i, j] = indexToCoordinates(pawnSquare);
  int dir = color == W ? +1 : -1;
  return ((ej - j) == 1 || (ej - j) == -1) && i + dir == ei;
}
