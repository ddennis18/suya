#include <iostream>
#include "board/board.h"
#include "board/FEN.h"
#include "movegen/MoveGenerator.h"
#include "utils/utils.h"

int main() {
  std::string fen = "";
  std::getline(std::cin, fen);
  Board b = convertFEN(fen);
  std::cout<<b.toString();

  auto moves = generateMoves(b);
  std::cout<<"done";
}