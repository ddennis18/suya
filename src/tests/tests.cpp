//
// Created by DENNIS on 8/19/2026.
//

#include "tests.h"

void testBoardRepresentation(std::string FEN) {
  auto b = convertFEN(FEN);
  std::cout << b.toString() << '\n';
}

void testMoveGeneration(std::string FEN) {
  auto b = convertFEN(FEN);
  auto moves = generateMoves(b);
  std::cout << "Total Number of Possible Moves: " << moves.lenght() << '\n';
  for (int i = 0; i < moves.lenght(); i++) {
    Move move = moves[i];
    std::cout << pieceTypeStringTable[pieceType(move.piece)] << ": " << move.start << "->" << move.target;
    if (move.captures) {
      std::cout << " captures: " << move.capturedPiece;
    }
    if (move.isEnpassant) {
      std::cout << " enpasant";
    }
    if (move.isCastling) {
      std::cout << " castle";
    }
    if (move.isPromotion) {
      std::cout << " promotingTo " << pieceTypeStringTable[move.promotedTo];
    }
    std::cout << std::endl;
  }
}

int lookDeep(Board b, int depth) {
  auto moves = generateMoves(b);
  if (depth == 1) {
    return moves.lenght();
  }
  int m = 0;
  for (int i = 0; i < moves.lenght(); i++) {
    Board newBoard = b.copyAndApplyMove(moves[i]);
    m += lookDeep(newBoard, depth - 1);
  }
  return m;
}

void testMoveGenerationAtDepth(std::string FEN, int depth) {
  auto b = convertFEN(FEN);
  int result = lookDeep(b, 3);
  std::cout << "Nodes " << result << " depth: " << depth << std::endl;
}
