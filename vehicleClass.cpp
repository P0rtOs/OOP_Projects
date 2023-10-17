#include <iostream>
#include "vehicleClass.h"


Vehicle::Vehicle() {
	std::cout << "vehicle created" << std::endl;
}

Vehicle::~Vehicle() {
	std::cout << "vehicle deleated" << std::endl;
}

int Vehicle::getVehicleId() {
	return this->vehicleId;
}

Road Vehicle::getVehicleRoad() {
	return this->vehicleRoad;
}

void Vehicle::setVehicleRoad(Road thisRoad) {
	this->vehicleRoad = thisRoad;
}

std::string Vehicle::getVehicleType() {
	return this->vehicleType;
}