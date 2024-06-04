
#pragma once
#include "pointClass.h"

#include <vector>
#include <memory>

class PointManager {
private:
    std::vector<std::unique_ptr<Point>> points;

public:
    PointManager() = default;
    ~PointManager() = default;

    void addPoint(std::unique_ptr<Point> point);
    void removePoint(int pointId);
    Point* getPoint(int pointId);
    std::vector<std::unique_ptr<Point>>& getAllPoints();
    std::vector<Point*> getNearestPoints(double x, double y, int count);  // New method
    std::vector<Point*> getAccessiblePoints(int startPointId);
};
