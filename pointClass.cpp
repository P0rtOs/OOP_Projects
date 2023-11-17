#include <iostream>
#include "pointClass.h"

Point::Point() {
	std::cout << "Point created using default constuctor.\n";
}

Point::Point(int pointId, double pointX, double pointY) {
	std::cout << "Point created with settings:" << pointId << " " << pointX << " " << pointY << "\n";
	this->setPointId(pointId);
	this->setPointX(pointX);
	this->setPointY(pointY);
}

Point::~Point() {
	std::cout << "Point deleted. \n";
}

int Point::getPointId() {
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

void Point::addNeighbor(int neighborId) {
	neighbors.push_back(neighborId);
}