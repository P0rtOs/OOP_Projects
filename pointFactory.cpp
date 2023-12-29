#include "pointFactory.h"

#include <iostream>

std::unique_ptr<Point> PointFactory::createPoint(int pointId, double x, double y) {
    return std::make_unique<Point>(pointId, x, y);
}

std::unique_ptr<Point> PointFactory::createPoint(int pointId, double x, double y, std::vector<std::unique_ptr<Connection>>& connections) {
    // Create a Point and pass the connections
    std::cout << "Point (id #" << pointId << ") created (" << x << "," << y << "). Connections: \n";
    for (const auto& connection : connections) {
        std::cout << "    to point (id #" << connection->getNeighborId()
            << ") | ticksToTraverse: " << connection->getTicksToTraverse()
            << " | weight: " << connection->getWeightLimit() << std::endl;
    }
    std::cout << "\n";
    auto point = std::make_unique<Point>(pointId, x, y);
    for (auto& connection : connections) {
        point->addConnection(std::move(connection));
    }

    return point;
}
