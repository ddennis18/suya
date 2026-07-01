//
// Created by DENNIS on 6/26/2026.
//

#ifndef SUYA_UTILS_H
#define SUYA_UTILS_H

#include <string>
#include <tuple>
#include "../board//board.h"

bool withinBoard(int n);

bool withinBoard(int i, int j);

int pieceType(int p);

//NOTE: this breaks on an empty square so check if the square is empty before hand
int pieceColor(int p);

bool isEmpty(int p);

std::tuple<int, int> indexToCoordinates(int i);

int getSquareColor(int p);

int getSquareColor(int i, int j);

std::array<int, 8> getSquaresOnDiagonal(int i, int j, int dir);


#endif //SUYA_UTILS_H
