#include "movementStrategyClass.h"
#include "globalObjects.h"

#include <iostream>
#include <queue>
#include <limits>
#include <unordered_map>


bool isConnected(int pointId1, int pointId2) {
    Point* point1 = globalPointManager.getPoint(pointId1);
    if (point1) {
        for (const auto& connection : point1->getNeighbors()) {
            if (connection->getNeighborId() == pointId2) {
                return true;
            }
        }
    }
    return false;
}

MovementStrategy::MovementStrategy() {
    std::cout << "Created Movement Strategy instance. It should be created paralel to each vehicle." << std::endl;
}

std::vector<Point*> MovementStrategy::dijkstraShortestPath(int sourceId, int targetId, Vehicle& vehicle) {
    const auto& allPoints = globalPointManager.getAllPoints();
    std::unordered_map<int, int> idToIndex;
    for (size_t i = 0; i < allPoints.size(); ++i) {
        idToIndex[allPoints[i]->getPointId()] = static_cast<int>(i);
    }

    std::vector<double> distance(allPoints.size(), std::numeric_limits<double>::infinity());
    std::vector<int> predecessor(allPoints.size(), -1);
    distance[idToIndex[sourceId]] = 0.0;

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;
    pq.push({ 0.0, idToIndex[sourceId] });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (allPoints[u]->getPointId() == targetId) break;

        for (const auto& connection : allPoints[u]->getNeighbors()) {
            int v = idToIndex[connection->getNeighborId()];
            double weight = static_cast<double>(connection->getTicksToTraverse());

            if (isConnected(allPoints[u]->getPointId(), allPoints[v]->getPointId())) {
                if (distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                    pq.push({ distance[v], v });
                }
            }
        }
    }

    std::vector<Point*> shortestPath;
    for (int at = idToIndex[targetId]; at != -1; at = predecessor[at]) {
        shortestPath.push_back(allPoints[at].get());  // Accessing the raw pointer
    }
    std::reverse(shortestPath.begin(), shortestPath.end());

    if (shortestPath.empty() || shortestPath.front()->getPointId() != sourceId) {
        Point* startPoint = allPoints[idToIndex[sourceId]].get();
        if (startPoint) {
            shortestPath.insert(shortestPath.begin(), startPoint);
        }
    }
    vehicle.setPath(shortestPath);
    return shortestPath;
}



StandartCarMovingStrategy::StandartCarMovingStrategy() {}


std::string StandartCarMovingStrategy::returnStrategyType() {
    return "StandartCar";
}


Point* StandartCarMovingStrategy::returnRandomDestination(int currentPointId) {
    auto accessiblePoints = globalPointManager.getAccessiblePoints(currentPointId);
    if (accessiblePoints.empty()) return nullptr;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex = std::rand() % accessiblePoints.size();
    return accessiblePoints[randomIndex];
}


Point* StandartCarMovingStrategy::returnStartingPoint() {
    const auto& points = globalPointManager.getAllPoints();
    if (!points.empty()) {
        int randomIndex = std::rand() % points.size();
        Point* startPoint = points[randomIndex].get();
        std::cout << "Standard Car assigned to start at point (id #" << startPoint->getPointId() << "). (\"" << startPoint->getPointType() << "\")\n\n";
        return startPoint;
    }
    else {
        std::cerr << "Warning: No starting point found for Standard Car. Defaulting to point ID 0." << "\n\n";
        return globalPointManager.getPoint(0);
    }
}


TruckMovingStrategy::TruckMovingStrategy() {}

std::vector<Point*> getFilteredAccessiblePoints(int currentPointId, PointType type) {
    auto accessiblePoints = globalPointManager.getAccessiblePoints(currentPointId);
    std::vector<Point*> filteredPoints;
    for (Point* point : accessiblePoints) {
        if (point->getPointType() == type) {
            filteredPoints.push_back(point);
        }
    }
    return filteredPoints;
}

std::string TruckMovingStrategy::returnStrategyType() {
    return "Truck";
}

Point* TruckMovingStrategy::returnRandomDestination(int currentPointId) {
    auto filteredPoints = getFilteredAccessiblePoints(currentPointId, PointType::PostOffice);
    if (filteredPoints.empty() || filteredPoints.front()->getPointId() == currentPointId) {
        filteredPoints = getFilteredAccessiblePoints(currentPointId, PointType::House);
    }
    if (filteredPoints.empty()) return nullptr;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex = std::rand() % filteredPoints.size();
    return filteredPoints[randomIndex];
}

Point* TruckMovingStrategy::findRandomPointOfType(PointType type) {
    const auto& points = globalPointManager.getAllPoints();
    std::vector<Point*> filteredPoints;
    for (const auto& point : points) {
        if (point->getPointType() == type) {
            filteredPoints.push_back(point.get());
        }
    }

    if (!filteredPoints.empty()) {
        int randomIndex = std::rand() % filteredPoints.size();
        return filteredPoints[randomIndex];
    }

    return nullptr; // No points of the specified type found
}

Point* TruckMovingStrategy::returnStartingPoint() {
    Point* startPoint = findRandomPointOfType(PointType::PostOffice);
    if (!startPoint) {
        startPoint = findRandomPointOfType(PointType::House);
    }

    if (startPoint) {
        std::cout << "Truck assigned to start at point ID (id #" << startPoint->getPointId() << "). (\"" << startPoint->getPointType() << "\")\n\n";
    }
    else {
        std::cout << "No Post Office or House found. Defaulting to point ID 0." << "\n\n";
        startPoint = globalPointManager.getPoint(0);
    }

    return startPoint;
}


SchoolBusMovingStrategy::SchoolBusMovingStrategy()
    : headingToSchool(false) {
}

Point* SchoolBusMovingStrategy::returnStartingPoint() {
    school = findRandomSchool();
    if (!school) {
        school = findRandomPointOfType(PointType::PoliceStation);
        if (!school) {
            std::cout << "No school or police station found. Defaulting to point ID 0." << "\n\n";
            school = globalPointManager.getPoint(0);
        }
    }

    if (school) {
        std::cout << "School Bus assigned to start at point (id #" << school->getPointId() << "). (\"" << school->getPointType() << "\")\n\n";
    }
    else {
        std::cerr << "Warning: No starting point found for School Bus." << "\n\n";
    }
    return school;
}

std::string SchoolBusMovingStrategy::returnStrategyType() {
    return "SchoolBus";
}

Point* SchoolBusMovingStrategy::returnRandomDestination(int currentPointId) {
    if (headingToSchool) {
        headingToSchool = false;
        return school;
    }
    else {
        auto houses = getFilteredAccessiblePoints(currentPointId, PointType::House);
        if (houses.empty()) return nullptr;

        headingToSchool = true;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int randomIndex = std::rand() % houses.size();
        return houses[randomIndex];
    }
}

Point* SchoolBusMovingStrategy::returnRandomHouse() {
    const auto& points = globalPointManager.getAllPoints();
    std::vector<Point*> houses;
    for (const auto& point : points) {
        if (point->getPointType() == PointType::House) {
            houses.push_back(point.get());
        }
    }

    if (!houses.empty()) {
        int randomIndex = std::rand() % houses.size();
        return houses[randomIndex];
    }

    return nullptr; // No houses found
}

Point* SchoolBusMovingStrategy::findRandomPointOfType(PointType type) {
    const auto& points = globalPointManager.getAllPoints();
    std::vector<Point*> filteredPoints;
    for (const auto& point : points) {
        if (point->getPointType() == type) {
            filteredPoints.push_back(point.get());
        }
    }

    if (!filteredPoints.empty()) {
        int randomIndex = std::rand() % filteredPoints.size();
        return filteredPoints[randomIndex];
    }

    return nullptr; // No points of the specified type found
}


Point* SchoolBusMovingStrategy::findRandomSchool() {
    const auto& points = globalPointManager.getAllPoints();
    std::vector<Point*> schools;
    for (const auto& point : points) {
        if (point->getPointType() == PointType::School) {
            schools.push_back(point.get());
        }
    }

    if (!schools.empty()) {
        int randomIndex = std::rand() % schools.size();
        return schools[randomIndex];
    }

    return nullptr; // No schools found
}
