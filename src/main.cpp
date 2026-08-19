#include <chrono>
#include <iostream>
#include "board/board.h"
#include "board/FEN.h"
#include "./movegen/MoveGenerator.h"
#include "tests/tests.h"

int lookDeepCaptures(Board b, int depth) {
  auto moves = generateMoves(b);
  if (depth == 1) {
    int captures = 0;
    for (int i = 0; i < moves.lenght(); i++) {
      if (moves[i].isCastling) {
        captures++;
      }
    }
    return captures;
  }
  int captures = 0;
  for (int i = 0; i < moves.lenght(); i++) {
    Board newBoard = b.copyAndApplyMove(moves[i]);
    captures += lookDeepCaptures(newBoard, depth - 1);
  }
  return captures;
}

int main() {
  auto start = std::chrono::steady_clock::now();

  testMoveGenerationAtDepth(TEST_POSITIONS[0], 2);

  auto end = std::chrono::steady_clock::now();


  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "done finished in " << duration << '\n';
}
