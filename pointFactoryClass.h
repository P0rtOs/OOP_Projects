#pragma once
#include "pointClass.h"

#include <memory>
#include <vector>


class PointFactory {
public:
    // Метод для створення стандартного Point
    std::unique_ptr<Point> createPoint(int pointId, double x, double y);
    std::unique_ptr<Point> createPoint(int pointId, double x, double y, std::vector<std::unique_ptr<Connection>>& connections);
    // Тут можна додати додаткові методи для створення різних типів Point
};
