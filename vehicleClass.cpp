#include <iostream>
#include "vehicleClass.h"
#include <string>

// TODO: ƒопустим у нас машина будет спанитьс€ на точке и ждать. ѕо прошествию рандомного количества тиков, 
// movementStrategy должна дать ей конечную точку, к которой она будет ехать алгоритмом (каким еще надо подумать, возможно тоже рандом) 
// ѕо пришествию на точку, она должна стать и рандомно ждать следующих указаний.


Vehicle::Vehicle() : currentState(AT_POINT), currentPointId(0)
{
	std::cout << "Vehicle created using default constuctor. " << std::endl;
}

Vehicle::Vehicle(int vehicleId, int newCurrentPointId, int newGoalPointId, std::string vehicleType) : currentState(AT_POINT)
{
	this->setVehicleId(vehicleId);
	this->setVehiclePoint(newCurrentPointId);
	this->setVehicleGoalPoint(newGoalPointId);
	this->setVehicleType(vehicleType);

	std::cout << "Vehicle created with following parameters: " << this->getVehicleId() << " " << this->getVehicleType() << std::endl;
}

Vehicle::~Vehicle() {std::cout << "Vehicle deleted" << std::endl;}

int Vehicle::getVehicleId() { return this->vehicleId; }

void Vehicle::setVehicleId(int Id) { this->vehicleId = Id; }

void Vehicle::setVehicleType(std::string thisType) { this->vehicleType = thisType; }

std::string Vehicle::getVehicleType() { return this->vehicleType; }

void Vehicle::setVehiclePoint(int newPointId) { currentPointId = newPointId; }

void Vehicle::setVehicleRoad(const Connection& newConnection) { currentRoad = newConnection; }

void Vehicle::setVehicleGoalPoint(int newGoalPointId) { goalPointId = newGoalPointId; }

void Vehicle::moveToRoad(const Connection& road) {
	currentState = ON_ROAD;
	currentRoad = road;
}

void Vehicle::moveToPoint(int pointId) {
	currentState = AT_POINT;
	currentPointId = pointId;
}

std::string Vehicle::getLocationInfo() {
	std::string locationInfo;
	if (currentState == AT_POINT) {
		locationInfo = "Vehicle is at point ID " + std::to_string(currentPointId);
	}
	else if (currentState == ON_ROAD) {
		locationInfo = "Vehicle is on road to point ID " + std::to_string(currentRoad.getNeighborId());
	}
	return locationInfo;
}


void Vehicle::update() {
	movementStrategy->move(*this);
}

Car::Car() : numberOfDoors(4) {}

Car::Car(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, int doors)
	: Vehicle(vehicleId, newVehicleCurrentPointId, newVehicleGoalPoint, vehicleType), numberOfDoors(doors) {}

int Car::getNumberOfDoors()
{
	return numberOfDoors;
}

void Car::setNumberOfDoors(int doors)
{
	numberOfDoors = doors;
}

Truck::Truck() : aim(default_point) {} // конструткор по стандарту дл€ ц≥л≥ вантаж≥вки, можливо €кийсь центр лог≥стики

Truck::Truck(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point point)
	: Vehicle(vehicleId, newVehicleCurrentPointId, newVehicleGoalPoint, vehicleType), aim(point) {}

Point Truck::getAim()
{
	return aim;
}

void Truck::setAim(Point point)
{
	aim = point;
}

SchoolBus::SchoolBus() : bus_stations_to_serve(default_vector), school_to_serve(default_point) {}

SchoolBus::SchoolBus(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point school_to_serve1, std::vector<Point> bus_stations_to_serve1)
	: Vehicle(vehicleId, newVehicleCurrentPointId, newVehicleGoalPoint, vehicleType), school_to_serve(school_to_serve1), bus_stations_to_serve(bus_stations_to_serve1) {}

Point SchoolBus::getSchool()
{
	return school_to_serve;
}

void SchoolBus::setSchool(Point school_to_serve1)
{
	school_to_serve = school_to_serve1;
}

std::vector<Point> SchoolBus::getbus_stations_to_serve()
{
	return bus_stations_to_serve;
}

void SchoolBus::setbus_stations_to_serve(std::vector<Point> bus_stations_to_serve1)
{
	bus_stations_to_serve = bus_stations_to_serve1;
}