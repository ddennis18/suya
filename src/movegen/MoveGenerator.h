//
// Created by DENNIS on 6/27/2026.
//

#ifndef SUYA_MOVEGEN_H
#define SUYA_MOVEGEN_H

#include <list>
#include "./Move.h"
#include "../board/board.h"

MoveList generateMoves(Board &);

bool pawnCanCaptureEnpassant(int enpassantSquare, int pawnSquare, int color);

template<typename Func> void generateRookMoves(const Board &b, Func appendMove, const int i, const int j);

template<typename Func> void generateBishopMoves(const Board &b, Func appendMove, const int i, const int j);


#endif //SUYA_MOVEGEN_H
