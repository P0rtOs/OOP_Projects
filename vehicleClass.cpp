#include <iostream>
#include "vehicleClass.h"


Vehicle::Vehicle() {
	std::cout << "vehicle created" << std::endl;
}

Vehicle::Vehicle(int vehicleId, Road vehicleRoad, std::string vehicleType) {
	this->setVehicleId(vehicleId);
	this->setVehicleRoad(vehicleRoad);
	this->setVehicleType(vehicleType);

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

void Vehicle::setVehicleId(int Id) {
	this->vehicleId = Id;
}

void Vehicle::setVehicleRoad(Road thisRoad) {
	this->vehicleRoad = thisRoad;
}

void Vehicle::setVehicleType(std::string thisType) {
	this->vehicleType = thisType;
}

std::string Vehicle::getVehicleType() {
	return this->vehicleType;
}