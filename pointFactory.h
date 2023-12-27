#pragma once
#include "pointClass.h"

class PointFactory {
public:
    // Метод для створення стандартного Point
    Point* createPoint(int pointId, double x, double y);
    Point* createPoint(int pointId, double x, double y, std::vector<Connection*>& connection, int neightbourAmount);

    // Тут можна додати додаткові методи для створення різних типів Point
};
