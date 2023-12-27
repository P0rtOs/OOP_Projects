#pragma once
#include <vector>
#include "pointClass.h"

class PointManager {
private:
    std::vector<Point*> points;

public:
    PointManager() = default;
    ~PointManager() = default;

    void addPoint(Point* point);
    void removePoint(int pointId);
    Point* getPoint(int pointId);
    std::vector<Point*>& getAllPoints(); 
};
