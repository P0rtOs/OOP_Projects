#include <iostream>
#include "roadClass.h"

Road::Road(Point& roadStartPoint, Point& roadEndPoint, int& roadSpeed) {
    std::cout << "Road created from " << roadStartPoint.getPointId() << " to " << roadEndPoint.getPointId();
    this->roadSpeedLimit = roadSpeed;
    this->roadStartPoint = roadStartPoint;
    this->roadEndPoint = roadEndPoint;
}


Road::~Road() {
	std::cout << "Road deleted.";
}