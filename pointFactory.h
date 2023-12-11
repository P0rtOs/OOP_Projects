#pragma once
#include "pointClass.h"

class PointFactory {
public:
    // Метод для створення стандартного Point
    Point* createPoint(int pointId, double x, double y);

    // Тут можна додати додаткові методи для створення різних типів Point
};
