#include <iostream>
#include "roadClass.h"

Road::Road(Point roadStartPoint, Point roadEndPoint, double roadSpeed) {
	std::cout << "Road created from " << roadStartPoint.getPointId() << "to " << roadEndPoint.getPointId();
	this->roadSpeedLimit = roadSpeed;
}

Road::~Road() {
	std::cout << "Road deleted.";
}