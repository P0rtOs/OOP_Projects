#include <iostream>
#include "roadClass.h"

Road::Road() {
    std::cout << "Road created using default constructor\n";
}

Road::Road(Point& roadStartPoint, Point& roadEndPoint, int roadSpeed)
    : roadStartPoint(&roadStartPoint), roadEndPoint(&roadEndPoint) {
    std::cout << "Road created from " << roadStartPoint.getPointId() << " to " << roadEndPoint.getPointId() << std::endl;
    this->roadSpeedLimit = roadSpeed;
}



Road::~Road() {
	std::cout << "Road deleted.\n";
}

int Road::getRoadId() {
    return this->roadId;
}

Point* Road::getRoadStartPoint() {
    return this->roadStartPoint;
}

Point* Road::getRoadEndPoint() {
    return this->roadEndPoint;
}

int* Road::getSpeedLimit() {
    return &this->roadSpeedLimit;
}

std::ostream& operator<<(std::ostream& os, Road& road) {
    os << "Road from " << road.getRoadStartPoint()->getPointId() << " to " << road.getRoadEndPoint()->getPointId() << " with speed limit " << *(road.getSpeedLimit());
    return os;
}