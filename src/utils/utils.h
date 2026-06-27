//
// Created by DENNIS on 6/26/2026.
//

#ifndef SUYA_UTILS_H
#define SUYA_UTILS_H

#include <string>
#include <tuple>

bool withinBoard(int n);

int pieceType(int p);
int pieceColor(int p);
bool isEmpty(int p);
std::tuple<int, int> indexToCoordinates(int i);

#endif //SUYA_UTILS_H
