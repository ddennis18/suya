//
// Created by DENNIS on 8/19/2026.
//

#ifndef SUYA_TESTS_H
#define SUYA_TESTS_H

#include <string>
#include <iostream>
#include "../movegen/MoveGenerator.h"
#include "../board/FEN.h"

const std::string TEST_POSITIONS[2] = {
  "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",
  "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1"
};

void testBoardRepresentation(std::string FEN);

void testMoveGeneration(std::string FEN);

int lookDeep(Board b, int depth);

void testMoveGenerationAtDepth(std::string FEN, int depth);

#endif //SUYA_TESTS_H
