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

void Vehicle::setVehiclePoint(int newPointId) {
	currentPointId = newPointId;
}


Car::Car() : numberOfDoors(4) {}
Car::Car(int vehicleId, Road& vehicleRoad, std::string vehicleType, int doors)
	: Vehicle(vehicleId, vehicleRoad, vehicleType), numberOfDoors(doors) {}

int Car::getNumberOfDoors() {
    return numberOfDoors;
}

void Car::setNumberOfDoors(int doors) {
    numberOfDoors = doors;
}


Truck::Truck() : aim(default_point) {} //конструткор по стандарту для цілі вантажівки, можливо якийсь центр логістики
Truck::Truck(int vehicleId, Road& vehicleRoad, std::string vehicleType, Point point)
	: Vehicle(vehicleId, vehicleRoad, vehicleType), aim(point) {}

Point Truck::getAim() {
    return aim;
}

void Truck::setAim(Point point) {
    aim = point;
}



School_bus::School_bus() : bus_stations_to_serve(default_vector), school_to_serve(default_point) {}
School_bus::School_bus(int vehicleId, Road& vehicleRoad, std::string vehicleType, Point school_to_serve1, std::vector<Point> bus_stations_to_serve1)
    : Vehicle(vehicleId, vehicleRoad, vehicleType), school_to_serve(school_to_serve1), bus_stations_to_serve(bus_stations_to_serve1) {}

Point School_bus::getSchool() {
    return school_to_serve;
}

void School_bus::setSchool(Point school_to_serve1) {
    school_to_serve = school_to_serve1;
}


std::vector<Point> School_bus::getbus_stations_to_serve() {
    return bus_stations_to_serve;
}

void School_bus::setbus_stations_to_serve(std::vector<Point> bus_stations_to_serve1) {
    bus_stations_to_serve = bus_stations_to_serve1;
}