#include "pointFactory.h"

#include <iostream>

std::unique_ptr<Point> PointFactory::createPoint(int pointId, double x, double y) {
    return std::make_unique<Point>(pointId, x, y);
}

std::unique_ptr<Point> PointFactory::createPoint(int pointId, double x, double y, std::vector<std::unique_ptr<Connection>>& connections) {
    std::cout << "id: " << pointId << " " << x << " " << y;
    for (const auto& connection : connections) {
        std::cout << " N id " << connection->getNeighborId()
            << " ticks: " << connection->getTicksToTraverse()
            << " weight: " << connection->getWeightLimit() << std::endl;
    }

    // Create a Point and pass the connections
    auto point = std::make_unique<Point>(pointId, x, y);
    for (auto& connection : connections) {
        point->addConnection(std::move(connection));
    }
    return point;
}
