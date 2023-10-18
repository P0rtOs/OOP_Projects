#include <iostream>
#include "pointClass.h"

Point::Point() {
	std::cout << "Point created.";
}

Point::Point(int pointId, double pointX, double pointY) {
	std::cout << "Point created.";
}

Point::~Point() {
	std::cout << "Point deleted";
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

void Point::setPointX(double x) {
	this->pointX = x;
}

void Point::setPointY(double y) {
	this->pointY = y;
}