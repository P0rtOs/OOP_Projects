#include <iostream>
#include "pointClass.h"
#include "globalObjects.h"

using std::vector;

Point::Point() : pointId(-1)  {
	std::cout << "Point created using default constuctor.\n";
}

Point::Point(int pointId, double pointX, double pointY) {
	std::cout << "Point created with settings:" << pointId << " " << pointX << " " << pointY << "\n";
	this->setPointId(pointId);
	this->setPointX(pointX);
	this->setPointY(pointY);
}

Point::Point(int pointId, double pointX, double pointY, std::vector<Connection*> connections)
{
	std::cout << "Point created with settings:" << pointId << " " << pointX << " " << pointY << "\n";
	this->setPointId(pointId);
	this->setPointX(pointX);
	this->setPointY(pointY);
	this->setNeighbor(connections);
}

Point::~Point() {
	std::cout << "Point deleted. \n";
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

void Point::setPointId(int Id) {
	this->pointId = Id;
}
void Point::setPointX(double x) {
	this->pointX = x;
}

void Point::setPointY(double y) {
	this->pointY = y;
}

void Point::addConnection(int pointId, int ticks, double weightLimit) {
	// This method adds a connection without creating a symmetrical one
	neighbors.emplace_back(new Connection(pointId, ticks, weightLimit));
}

void Point::addNeighbor(int neighborId, int ticks = 3, double weightLimit = 10000) {
	Point* neighborPoint = globalPointManager.getPoint(neighborId);
	if (neighborPoint) {
		neighbors.emplace_back(new Connection(neighborId, ticks, weightLimit));
		neighborPoint->addConnection(this->pointId, ticks, weightLimit); // Add connection in the other direction
	}
	else {
		// Handle the error, e.g., log a message or throw an exception
		std::cerr << "Error - point doesn't exist" << std::endl;
	}
	
}

void Point::setNeighbor(std::vector<Connection*> connectionsToSet) {
	this->neighbors = connectionsToSet;
}

vector<Connection*> Point::getNeighbors() {
	return neighbors;
}

// TODO: ѕродумать, сколько тиков должна машина сто€ть в точке (и должна ли). Ќаписать разразнение типов точек (почта, дом, тд).