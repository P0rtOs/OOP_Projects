#include "pointManager.h"

void PointManager::addPoint(Point* point) {
    points.push_back(point);
}

// Потрібно переписати логіку тута
void PointManager::removePoint(int pointId) {
    auto it = std::remove_if(points.begin(), points.end(),
        [pointId](Point* p) { return p->getPointId() == pointId; });

    if (it != points.end()) {
        delete* it;  // Важливо: видаляємо об'єкт, на який вказує вказівник
        points.erase(it, points.end());
    }
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
std::vector<Point*> PointManager::getAllPoints() {
    return points;
}
