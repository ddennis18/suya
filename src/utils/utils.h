//
// Created by DENNIS on 6/26/2026.
//

#ifndef SUYA_UTILS_H
#define SUYA_UTILS_H

#include <string>
#include <tuple>

bool withinBoard(int n);

int pieceType(int p);

//NOTE: this breaks on an empty square so check if the square is empty before hand
int pieceColor(int p);
bool isEmpty(int p);
std::tuple<int, int> indexToCoordinates(int i);

#endif //SUYA_UTILS_H
