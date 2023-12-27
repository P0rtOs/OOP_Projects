#include <iostream>
#include "movementStrategyClass.h"
#include "globalObjects.h"
#include <queue>
#include <limits>

MovementStrategy::MovementStrategy(){
    std::cout << "Created Movement Strategy" << std::endl;
}



StandartCarMovingStrategy::StandartCarMovingStrategy() {}

void StandartCarMovingStrategy::move(Vehicle& vehicle) {
	std::cout << "Moving car" << std::endl;

}

std::string StandartCarMovingStrategy::returnStrategyType() {
    return "StandartCar";
}


Point* StandartCarMovingStrategy::returnRandomDestination(int currentPointId) {
    std::vector<Point*>& points = globalPointManager.getAllPoints();
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
        destination = points[randomIndex];

        if (!destination || points.size() == 1) { // Null pointer or only one point
            break;
        }
    } while (destination->getPointId() == startId);



    return destination;
}

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



vector<Point*> StandartCarMovingStrategy::dijkstraShortestPath(int sourceId, int targetId, Vehicle& vehicle) {
    // Initialize distances to points and predecessors
    vector<double> distance(globalPointManager.getAllPoints().size(), std::numeric_limits<double>::infinity());
    vector<int> predecessor(globalPointManager.getAllPoints().size(), -1);  // Use -1 to indicate no predecessor
    distance[sourceId] = 0.0;

    // Priority queue for processing points in order of increasing distance
    std::priority_queue<std::pair<double, int>, vector<std::pair<double, int>>, std::greater<>> pq;
    pq.push({ 0.0, sourceId });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // If we reached the target, we can stop the algorithm
        if (u == targetId) break;

        // Update distances to neighbors of point u
        for (const auto& connection : globalPointManager.getAllPoints()[u]->getNeighbors()) {
            int v = connection->getNeighborId();
            double weight = static_cast<double>(connection->getTicksToTraverse());

            // Check if there's an actual connection to this neighbor
            if (isConnected(u, v)) {
                // Apply relaxation
                if (distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;  // Store the predecessor for path reconstruction
                    pq.push({ distance[v], v });
                }
            }
        }
    }

    // Reconstruct the shortest path from source to target
    vector<Point*> shortestPath;
    for (int at = targetId; at != -1; at = predecessor[at]) {
        shortestPath.push_back(globalPointManager.getAllPoints()[at]);
    }
    std::reverse(shortestPath.begin(), shortestPath.end()); // Reverse to get the correct order
    // Check if the start point is included in the path, add it if not
    if (shortestPath.empty() || shortestPath.front()->getPointId() != sourceId) {
        Point* startPoint = globalPointManager.getPoint(sourceId);
        if (startPoint) {
            shortestPath.insert(shortestPath.begin(), startPoint);
        }
    }
    vehicle.setPath(shortestPath);
    return shortestPath;
}


// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  