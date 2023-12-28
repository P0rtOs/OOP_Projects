#include "movementStrategyClass.h"
#include "globalObjects.h"

#include <iostream>
#include <queue>
#include <limits>

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

MovementStrategy::MovementStrategy(){
    std::cout << "Created Movement Strategy instance. It should be created paralel to each vehicle." << std::endl;
}

std::vector<Point*> MovementStrategy::dijkstraShortestPath(int sourceId, int targetId, Vehicle& vehicle) {
    const auto& allPoints = globalPointManager.getAllPoints();
    std::vector<double> distance(allPoints.size(), std::numeric_limits<double>::infinity());
    std::vector<int> predecessor(allPoints.size(), -1);
    distance[sourceId] = 0.0;

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;
    pq.push({ 0.0, sourceId });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == targetId) break;

        for (const auto& connection : allPoints[u]->getNeighbors()) {
            int v = connection->getNeighborId();
            double weight = static_cast<double>(connection->getTicksToTraverse());

            if (isConnected(u, v)) {
                if (distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                    pq.push({ distance[v], v });
                }
            }
        }
    }

    std::vector<Point*> shortestPath;
    for (int at = targetId; at != -1; at = predecessor[at]) {
        shortestPath.push_back(allPoints[at].get());  // Accessing the raw pointer
    }
    std::reverse(shortestPath.begin(), shortestPath.end());

    if (shortestPath.empty() || shortestPath.front()->getPointId() != sourceId) {
        Point* startPoint = allPoints[sourceId].get();
        if (startPoint) {
            shortestPath.insert(shortestPath.begin(), startPoint);
        }
    }
    vehicle.setPath(shortestPath);
    return shortestPath;
}



StandartCarMovingStrategy::StandartCarMovingStrategy() {}

//void StandartCarMovingStrategy::move(Vehicle& vehicle) {
//	std::cout << "Moving car" << std::endl;
//
//}

std::string StandartCarMovingStrategy::returnStrategyType() {
    return "StandartCar";
}


Point* StandartCarMovingStrategy::returnRandomDestination(int currentPointId) {
    const auto& points = globalPointManager.getAllPoints();
    if (points.size() <= 1) {
        return nullptr;  // Return null if there are no points or only one point
    }

    // Seed the random number generator - typically done once at program start
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    int startId = currentPointId;  // Get the start point ID
    Point* destination = nullptr;
    do {
        int randomIndex = std::rand() % points.size();
        destination = points[randomIndex].get();

        if (!destination || points.size() == 1) { // Null pointer or only one point
            break;
        }
    } while (destination->getPointId() == startId);


    return destination;
}

Point* StandartCarMovingStrategy::returnStartingPoint() {
    const auto& points = globalPointManager.getAllPoints();
    if (!points.empty()) {
        int randomIndex = std::rand() % points.size();
        Point* startPoint = points[randomIndex].get();
        std::cout << "Standard Car assigned to start at point ID: " << startPoint->getPointId() << "\n\n";
        return startPoint;
    }
    else {
        std::cerr << "Warning: No starting point found for Standard Car. Defaulting to point ID 0." <<"\n\n";
        return globalPointManager.getPoint(0);
    }
}


TruckMovingStrategy::TruckMovingStrategy() {}

std::string TruckMovingStrategy::returnStrategyType() {
    return "Truck";
}

Point* TruckMovingStrategy::returnRandomDestination(int currentPointId) {
    const auto& points = globalPointManager.getAllPoints();
    if (points.size() <= 1) {
        return nullptr; // No valid destination
    }

    // Filter points to include only PostOffice and House types
    std::vector<Point*> filteredPoints;
    for (const auto& point : points) {
        PointType type = point->getPointType();
        if (type == PointType::PostOffice || type == PointType::House) {
            filteredPoints.push_back(point.get());
        }
    }

    if (filteredPoints.empty()) {
        return nullptr; // No PostOffice or House found
    }

    // Randomly select a destination from filtered points
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    Point* destination = nullptr;
    do {
        int randomIndex = std::rand() % filteredPoints.size();
        destination = filteredPoints[randomIndex];

    } while (destination && destination->getPointId() == currentPointId);
    return destination;
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
        std::cout << "Truck assigned to start at point ID: " << startPoint->getPointId() << "\n\n";
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
        std::cout << "School Bus assigned to start at point ID: " << school->getPointId() << "\n\n";
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
        headingToSchool = true;
        return returnRandomHouse();
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


// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  