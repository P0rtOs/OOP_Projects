#include "pointManager.h"

#include <iostream>


void PointManager::addPoint(std::unique_ptr<Point> point) {
    points.push_back(std::move(point));  
}

void PointManager::removePoint(int pointId) {
    auto it = std::remove_if(points.begin(), points.end(),
        [pointId](const std::unique_ptr<Point>& p) { return p->getPointId() == pointId; });
    if (it != points.end()) {
        points.erase(it, points.end());
    }
}

Point* PointManager::getPoint(int pointId) {
    for (const auto& p : points) {
        if (p->getPointId() == pointId) {
            return p.get();  
        }
    }
    return nullptr;  
}


std::vector<std::unique_ptr<Point>>& PointManager::getAllPoints() {
    return points;
}
