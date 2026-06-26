//
// Created by DENNIS on 6/26/2026.
//

#include "board.h"

std::string Board::toString() {
  std::string ret = "\n";
  for (int i =7;i >= 0; i--) {
    for (int j = 7; j >= 0 ; j--) {
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
    ret+="|\n";
  }
  return ret;
}
