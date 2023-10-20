#include <iostream>
#include "vehicleClass.h"


Vehicle::Vehicle() {
	std::cout << "Vehicle created using default constuctor. " << std::endl;
}

Vehicle::Vehicle(int vehicleId, Road& vehicleRoad, std::string vehicleType) : vehicleRoad(&vehicleRoad) {
	this->setVehicleId(vehicleId);
	this->setVehicleRoad(vehicleRoad);
	this->setVehicleType(vehicleType);

	std::cout << "Vehicle created with following parameters: " << this->getVehicleId() << " " << this->getVehicleRoad()->getRoadId() << " " << this->getVehicleType() << std::endl;
}

Vehicle::~Vehicle() {
	std::cout << "Vehicle deleted" << std::endl;
}

int Vehicle::getVehicleId() {
	return this->vehicleId;
}

Road* Vehicle::getVehicleRoad() {
	return this->vehicleRoad;
}

void Vehicle::setVehicleId(int Id) {
	this->vehicleId = Id;
}

void Vehicle::setVehicleRoad(Road& thisRoad) {
	this->vehicleRoad = &thisRoad;
}

void Vehicle::setVehicleType(std::string thisType) {
	this->vehicleType = thisType;
}

std::string Vehicle::getVehicleType() {
	return this->vehicleType;
}