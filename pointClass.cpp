#include "pointClass.h"
#include "globalObjects.h"

#include <iostream>

using std::vector;

Point::Point() : pointId(-1)  {
	neighbors = std::vector<std::unique_ptr<Connection>>(); // Proper initialization
	std::cout << "Point created using default constuctor. This is probably a bug. Possibly. Definitely.\n";
	
}

Point::Point(int pointId, double pointX, double pointY) {
	neighbors = std::vector<std::unique_ptr<Connection>>(); // Proper initialization	
	this->setPointId(pointId);
	this->setPointX(pointX);
	this->setPointY(pointY);
	this->setPointType(static_cast<PointType>(rand() % static_cast<int>(PointType::Last)));
	std::cout << "Point (id #" << getPointId() << ") created on coordinates (" << getPointX() << "," << getPointY() << ").\n";

}

Point::Point(int pointId, double pointX, double pointY, std::vector<Connection*> connections)
{
	neighbors = std::vector<std::unique_ptr<Connection>>(); // Proper initialization
	this->setPointId(pointId);
	this->setPointX(pointX);
	this->setPointY(pointY);
	this->setNeighbor(connections);
	this->setPointType(static_cast<PointType>(rand() % static_cast<int>(PointType::Last)));
	std::cout << "Point (id #" << getPointId() << ") created on coordinates ( " << getPointX() << "," << getPointY() << ") with connections.\n";

}

Point::Point(int pointId, double pointX, double pointY, PointType pointType) {
	neighbors = std::vector<std::unique_ptr<Connection>>(); // Proper initialization	
	this->setPointId(pointId);
	this->setPointX(pointX);
	this->setPointY(pointY);
	this->setPointType(pointType);
	std::cout << "Point (id #" << getPointId() << ") created on coordinates (" << getPointX() << "," << getPointY() << ").\n";

}

Point::Point(int pointId, double pointX, double pointY, PointType pointType, std::vector<Connection*> connections)
{
	neighbors = std::vector<std::unique_ptr<Connection>>(); // Proper initialization
	this->setPointId(pointId);
	this->setPointX(pointX);
	this->setPointY(pointY);
	this->setPointType(pointType);
	this->setNeighbor(connections);
	std::cout << "Point (id #" << getPointId() << ") created on coordinates ( " << getPointX() << "," << getPointY() << ") with connections.\n";

}


const int Point::getPointId() {
	return this->pointId;
}

double Point::getPointX() {
	return this->pointX;
}

double Point::getPointY() {
	return this->pointY;
}
PointType Point::getPointType() {
	return this->pointType;
}

void Point::setPointId(int Id) {
	this->pointId = Id;
}
void Point::setPointX(double x) {
	this->pointX = x;
}

void Point::setPointY(double y) {
	this->pointY = y;
}
void Point::setPointType(PointType pointType) {
	this->pointType = pointType;
}

void Point::addConnection(int pointId, int ticks, double weightLimit) {
	neighbors.emplace_back(std::make_unique<Connection>(pointId, ticks, weightLimit));
}

void Point::addConnection(std::unique_ptr<Connection> connection) {
	neighbors.push_back(std::move(connection));  // Move the unique_ptr to the vector
}

// Check if a connection to a specific point already exists
bool Point::hasConnection(int pointId) const {
	for (const auto& conn : neighbors) {
		if (conn->getNeighborId() == pointId) {
			return true;
		}
	}
	return false;
}

void Point::addNeighbor(int neighborId, int ticks, double weightLimit) {
	auto& allPoints = globalPointManager.getAllPoints();
	// Find the neighbor point in the globalPointManager
	auto it = std::find_if(allPoints.begin(), allPoints.end(),
		[neighborId](const std::unique_ptr<Point>& p) { return p->getPointId() == neighborId; });

	if (it != allPoints.end()) {
		// Add connection to this point
		addConnection(neighborId, ticks, weightLimit);

		// Check to avoid adding a connection if it already exists
		if (!(*it)->hasConnection(this->pointId)) {
			// Add a connection in the other direction
			(*it)->addConnection(this->pointId, ticks, weightLimit);
		}
	}
	else {
		std::cerr << "Error - neighbor point does not exist" << std::endl;
	}
}

void Point::setNeighbor(std::vector<Connection*> connectionsToSet) {
	neighbors.clear();
	for (const auto* conn : connectionsToSet) {
		neighbors.push_back(std::make_unique<Connection>(*conn));
	}
}

std::vector<Connection*> Point::getNeighbors() {
	std::vector<Connection*> rawPointers;
	for (const auto& neighbor : neighbors) {
		rawPointers.push_back(neighbor.get());  // get() returns the raw pointer
	}
	return rawPointers;
}
