#include "pointManagerClass.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>


void PointManager::addPoint(std::unique_ptr<Point> point) {
    points.push_back(std::move(point));  // Use std::move to transfer ownership
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
            return p.get();  // get() returns the raw pointer
        }
    }
    return nullptr;  // Or throw an exception if appropriate
}

std::vector<Point*> PointManager::getNearestPoints(double x, double y, int count) {
    std::vector<Point*> nearestPoints;
    std::vector<std::pair<double, Point*>> distances;

    // Calculate the Euclidean distance between the given coordinates and each point
    for (const auto& p : points) {
        double dx = p->getPointX() - x;
        double dy = p->getPointY() - y;
        double distance = std::sqrt(dx * dx + dy * dy);
        distances.push_back({ distance, p.get() });
    }

    // Sort the distances
    std::sort(distances.begin(), distances.end(),
        [](const std::pair<double, Point*>& a, const std::pair<double, Point*>& b) {
            return a.first < b.first;
        });

    // Select the nearest points
    for (int i = 0; i < count && i < distances.size(); ++i) {
        nearestPoints.push_back(distances[i].second);
    }

    return nearestPoints;
}

std::vector<Point*> PointManager::getAccessiblePoints(int startPointId) {
    std::vector<Point*> accessiblePoints;
    std::unordered_set<int> visited;
    std::queue<int> toVisit;

    toVisit.push(startPointId);
    visited.insert(startPointId);

    while (!toVisit.empty()) {
        int currentId = toVisit.front();
        toVisit.pop();
        Point* currentPoint = getPoint(currentId);
        if (currentPoint) {
            accessiblePoints.push_back(currentPoint);
            for (const auto& connection : currentPoint->getNeighbors()) {
                int neighborId = connection->getNeighborId();
                if (visited.find(neighborId) == visited.end()) {
                    toVisit.push(neighborId);
                    visited.insert(neighborId);
                }
            }
        }
    }

    return accessiblePoints;
}

// Тута вже не потрібно переписувати логіку
std::vector<std::unique_ptr<Point>>& PointManager::getAllPoints() {
    return points;
}
