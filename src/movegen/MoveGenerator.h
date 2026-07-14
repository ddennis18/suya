//
// Created by DENNIS on 6/27/2026.
//

#ifndef SUYA_MOVEGEN_H
#define SUYA_MOVEGEN_H

#include <list>
#include "./Move.h"
#include "../board/board.h"

MoveList generateMoves(const Board &);

bool pawnCanCaptureEnpassant(int enpassantSquare, int pawnSquare, int color);

void generateRookMoves(const Board &b, MoveList &moveList, const int i, const int j);

void generateBishopMoves(const Board &b, MoveList &moveList, const int i, const int j);


#endif //SUYA_MOVEGEN_H
