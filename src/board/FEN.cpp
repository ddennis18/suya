//
// Created by DENNIS on 6/26/2026.
//

#include "./FEN.h"

Board convertFEN(std::string FEN) {
  Board b;
  std::stringstream ss(FEN);

  std::string pieceData;
  std::string activeColor;
  std::string castlingRight;
  std::string enpassant;
  std::string halfMoveClockBuff;
  std::string fullMoveClockBuff;

  ss >> pieceData;
  ss >> activeColor;
  ss >> castlingRight;
  ss >> enpassant;
  ss >> halfMoveClockBuff;
  ss >> fullMoveClockBuff;

  int i = 7;
  //start from the last rank
  while (i >= 0) {
    int j = 0;
    for (const char c: pieceData) {
      if (std::isalpha(c)) {
        if (c == 'p') {
          b.squares[i][j] = 9; //black pawn
        } else if (c == 'n') {
          b.squares[i][j] = 10; //black knight
        } else if (c == 'b') {
          b.squares[i][j] = 11; //black bishop
        } else if (c == 'r') {
          b.squares[i][j] = 12; //black rook
        } else if (c == 'q') {
          b.squares[i][j] = 13; //black queen
        } else if (c == 'k') {
          b.squares[i][j] = 14; //black king
        } else if (c == 'P') {
          b.squares[i][j] = 1; //black pawn
        } else if (c == 'N') {
          b.squares[i][j] = 2; //black knight
        } else if (c == 'B') {
          b.squares[i][j] = 3; //black bishop
        } else if (c == 'R') {
          b.squares[i][j] = 4; //black rook
        } else if (c == 'Q') {
          b.squares[i][j] = 5; //black queen
        } else if (c == 'K') {
          b.squares[i][j] = 6; //black king
        }
      } else if (std::isdigit(c)) {
        const int d = c - '0'; //convert to number;
        j += d - 1;
      } else if (c == '/') {
        i -= 1;
        j = -1;
      }
      j += 1;
    }
    i -= 1;
  }

  b.whiteToMove = (activeColor == "w");

  if (castlingRight != "-") {
    b.whiteKingSideCastlingRight = castlingRight.contains('K');
    b.whiteQueenSideCastlingRight = castlingRight.contains('Q');
    b.blackKingSideCastlingRight = castlingRight.contains('k');
    b.blackQueenSideCastlingRight = castlingRight.contains('q');
  }

  if (enpassant == "-") {
    b.enpassantSquare = -1;
  } else {
    const int file = static_cast<unsigned char>(enpassant[0]) - 'a';
    const int rank = static_cast<unsigned char>(enpassant[1]) - '1';
    b.enpassantSquare = rank * 8 + file;
  }

  b.halfMoveClock = stoi(halfMoveClockBuff);
  b.fullMoveClock = stoi(fullMoveClockBuff);

  return b;
}

std::string convertBoardToFEN(Board b) {
  std::string FEN = "";
  int emptySpaceCounter = 0;
  for (int i = 7; i >= 0; i--) {
    for (int j = 0; j < 8; j++) {
      int s = b.getSquare(i, j);
      if (s == EMPTY)
        emptySpaceCounter++;
      else {
        if (emptySpaceCounter != 0)
          FEN.append(std::to_string(emptySpaceCounter));
        char l = pieceTypeStringTable[pieceType(s)];
        if (pieceColor(s) == B) {
          l = tolower(l);
        }
        FEN.push_back(l);
        emptySpaceCounter = 0;
      }
    }
    if (emptySpaceCounter != 0)
      FEN.append(std::to_string(emptySpaceCounter));
    emptySpaceCounter = 0;
    if (i != 0)
      FEN.append("/");
  }

  FEN += b.whiteToMove ? " w " : " b ";

  std::string castling = "";
  if (b.whiteKingSideCastlingRight) castling += "K";
  if (b.whiteQueenSideCastlingRight) castling += "Q";
  if (b.blackKingSideCastlingRight) castling += "k";
  if (b.blackQueenSideCastlingRight) castling += "q";
  if (castling == "")
    castling = "-";
  FEN += castling;

  if (b.enpassantSquare != -1) {
    auto [ei, ej] = indexToCoordinates(b.enpassantSquare);
    std::string e = "";
    e.push_back(static_cast<char>('a' + ej));
    e.append(std::to_string(ei + 1));
    FEN += " " + e + " ";
  } else {
    FEN += " - ";
  }

  FEN.append(std::to_string(b.halfMoveClock));
  FEN += " ";
  FEN.append(std::to_string(b.fullMoveClock));
  return FEN;
}
