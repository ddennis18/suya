#include <iostream>
#include "board/board.h"
#include "board/FEN.h"
#include "movegen/MoveGenerator.h"
#include "utils/utils.h"

int main() {
  // std::string fen = "";
  // std::getline(std::cin, fen);
  // Board b = convertFEN(fen);

  Board b = convertFEN("rnbqkbnr/pppppppp//8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  std::cout << b.toString();

  auto moves = generateMoves(b);
  std::cout << "Total Number of Possible Moves: " << moves.lenght() << '\n';
  for (int i = 0; i < moves.lenght(); i++) {
    Move move = moves[i];
    std::cout << pieceTypeStringTable[pieceType(move.piece)] << ": " << move.start << "->" << move.target;
    if (move.captures) {
      std::cout << " captures: " << move.capturedPiece;
    }
    std::cout << std::endl;
  }

  std::cout << "done" << '\n';
}
