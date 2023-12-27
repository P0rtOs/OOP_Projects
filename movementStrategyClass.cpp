#include <iostream>
#include "movementStrategyClass.h"
#include <queue>
#include <limits>

MovementStrategy::MovementStrategy(PointManager* pm) : pointManager(pm) {}

void MovementStrategy:: setPointManager(PointManager* pm) {
    pointManager = pm;
}


StandartCarMovingStrategy::StandartCarMovingStrategy(PointManager* pm) : MovementStrategy(pm) {}

void StandartCarMovingStrategy::move(Vehicle& vehicle) {
	std::cout << "Moving car" << std::endl;
}

vector<Point*> StandartCarMovingStrategy::dijkstraShortestPath(int sourceId, int targetId, Vehicle& vehicle) {
    // Initialize distances to points and predecessors
    vector<double> distance(pointManager->getAllPoints().size(), std::numeric_limits<double>::infinity());
    vector<int> predecessor(pointManager->getAllPoints().size(), -1);  // Use -1 to indicate no predecessor
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
        for (const auto& connection : pointManager->getAllPoints()[u]->getNeighbor()) {
            int v = connection->getNeighborId();
            double weight = static_cast<double>(connection->getTicksToTraverse());
            // Apply relaxation
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                predecessor[v] = u;  // Store the predecessor for path reconstruction
                pq.push({ distance[v], v });
            }
        }
    }

    // Reconstruct the shortest path from source to target
    vector<Point*> shortestPath;
    for (int at = targetId; at != -1; at = predecessor[at]) {
        shortestPath.push_back(pointManager->getAllPoints()[at]);
    }
    std::reverse(shortestPath.begin(), shortestPath.end()); // Reverse to get the correct order
    vehicle.setPath(shortestPath);
    return shortestPath;
}
// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  