#include "pointManager.h"

void PointManager::addPoint(Point* point) {
    points.push_back(point);
}

// Потрібно переписати логіку тута
void PointManager::removePoint(int pointId) {
    for (auto& point : points) {
        if (point->getPointId() == pointId) {
            delete point;
            point = nullptr; // Nullify the pointer after deleting
            break; // Since pointId is unique, break after finding the first match
        }
    }
    points.erase(std::remove(points.begin(), points.end(), nullptr), points.end());
}

Point* PointManager::getPoint(int pointId) {
    auto it = std::find_if(points.begin(), points.end(),
        [pointId](Point* p) { return p->getPointId() == pointId; });

    if (it != points.end()) {
        return *it;
    }

    return nullptr;
}
// Тута вже не потрібно переписувати логіку
std::vector<Point*>& PointManager::getAllPoints() {
    return points;
}
