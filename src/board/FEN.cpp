//
// Created by DENNIS on 6/26/2026.
//

#include "./FEN.h"

Board convertFEN(std::string FEN) {
  //half move clock and full move clock is not need atp
  Board b;
  std::stringstream ss(FEN);

  std::string pieceData;
  std::string activeColor;
  std::string castlingRight;
  std::string enpassant;

  ss>>pieceData;
  ss>>activeColor;
  ss>>castlingRight;
  ss>>enpassant;

  int i = 7;
  //start from the last rank
  while (i>=0) {
    int j = 7;
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
      }
      else if (std::isdigit(c)) {
        const int d = c - '0'; //convert to number;
        j-=d-1;
      }
      else if (c=='/') {
        i-=1;
        j=8;
      }
      j-=1;
    }
    i-=1;
  }

  return b;
}
