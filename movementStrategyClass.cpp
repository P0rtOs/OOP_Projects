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


void StandartCarMovingStrategy::dijkstraShortestPath(int sourceId) {
    // Ініціалізація відстаней до вершин
    std::vector<double> distance(pointManager->getAllPoints().size(), std::numeric_limits<double>::infinity());
    distance[sourceId] = 0.0;

    // Пріорітетна черга для обробки вершин у порядку зростання відстані
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;
    pq.push({ 0.0, sourceId });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Оновлення відстаней до сусідів вершини u
        for (const auto& connection : graph[u].neighbors) {
            int v = connection.neighborId;
            // Застосовуємо релаксацію
            if (distance[v] > distance[u] + 1.0) {
                distance[v] = distance[u] + 1.0;
                pq.push({ distance[v], v });
            }
        }
    }

    // Виведення результатів
    for (int i = 0; i < pointManager->getAllPoints().size(); ++i) {
        std::cout << "Shortest distance from " << sourceId << " to " << i << ": " << distance[i] << std::endl;
    }
}
// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  