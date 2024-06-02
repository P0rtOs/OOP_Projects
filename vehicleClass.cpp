#include <iostream>

#include "vehicleClass.h"
#include "globalObjects.h"
#include <string>
#include <algorithm>



Connection* findConnection(int pointAId, int pointBId) {
	Point* pointA = globalPointManager.getPoint(pointAId);
	Point* pointB = globalPointManager.getPoint(pointBId);

	if (!pointA || !pointB) {
		return nullptr;
	}

	for (Connection* conn : pointA->getNeighbors()) {
		if (conn && conn->getNeighborId() == pointBId) {
			return const_cast<Connection*>(conn);
		}
	}

	return nullptr;
}

Vehicle::Vehicle() : currentState(AT_POINT), currentPointId(0)
{
	std::cout << "Vehicle created using default constuctor. This is definitely a bug." << std::endl;
}
Vehicle::Vehicle(int vehicleId, std::string vehicleType) : currentState(AT_POINT)
{
	this->setVehicleId(vehicleId);
	this->setVehicleType(vehicleType);

	std::cout << getVehicleType() << " (id #" << this->getVehicleId() << ") created" << ".\n";
}
Vehicle::~Vehicle() {
	delete movementStrategy;
	path.clear();
	std::cout << getVehicleType() << " (id #" << getVehicleId() << ") deleted." << std::endl;
}

int Vehicle::getVehicleId() { return this->vehicleId; }

void Vehicle::setVehicleId(int Id) { this->vehicleId = Id; }

void Vehicle::setVehicleType(std::string thisType) { this->vehicleType = thisType; }

std::string Vehicle::getVehicleType() { return this->vehicleType; }

int Vehicle::getCurrentPointId() {
	return this->currentPointId;
}

Connection* Vehicle::getCurrentRoad() {
	return this->currentRoad;
}

void Vehicle::setVehiclePoint(int newPointId) { currentPointId = newPointId; }

void Vehicle::setVehicleRoad(Connection* newConnection) { currentRoad = newConnection; }

void Vehicle::setPath(const std::vector<Point*>& newPath) {
	path = newPath;
	currentPathIndex = 0;
}

void Vehicle::moveToPoint(int pointId) {
	currentState = AT_POINT;
	currentPointId = pointId;
}

void Vehicle::setLocationState(LocationState state) {
	this->currentState = state;
}

std::string Vehicle::currentStatus() {
	std::string locationInfo;
	if (currentState == AT_POINT) {
		locationInfo = getVehicleType() + " (id #" + std::to_string(getVehicleId()) + ") waiting at point (id #" + std::to_string(currentPointId) + "). Waited for " + std::to_string(ticksAtCurrentPoint) + " tick(s).\n";
	}
	else if (currentState == ON_ROAD) {
		locationInfo = getVehicleType() + " (id #" + std::to_string(getVehicleId()) + ") moving to point (id #" + std::to_string(currentRoad->getNeighborId()) + "). Ticks remaining: " + std::to_string(ticksRemaining) + " tick(s).\n";
	}
	return locationInfo;
}

void Vehicle::update() {
	if (!path.empty() && currentPathIndex < path.size()) {
		if (currentState == AT_POINT) {
			if (canDepartFromPoint()) {
				moveToNextPointOnPath();
			}
		}
		else if (currentState == ON_ROAD) {
			--ticksRemaining;
			if (ticksRemaining <= 0) {
				currentState = AT_POINT;
				onArrivalToPoint();
			}
		}
	}
	else if (path.empty()) {

		std::cout << getVehicleType() << " (id #" << this->getVehicleId() << ") path empty - finding new path" << "\n";
		if (movementStrategy != nullptr) {
			Point* destination = movementStrategy->returnRandomDestination(this->getCurrentPointId());
			if (destination != nullptr) {
				std::cout << getVehicleType() << " (id #" << this->getVehicleId() << ") found new path, destination - #" << destination->getPointId() << " (type: " << destination->getPointType() << ")\n";;
				movementStrategy->dijkstraShortestPath(this->getCurrentPointId(), destination->getPointId(), *this);
			}
			else {
				std::cerr << "No destination found\n";
			}
		}
		else {
			std::cerr << "Error: movementStrategy is null.\n";
		}
	}
	ticksAtCurrentPoint++;
}

void Vehicle::moveToNextPointOnPath() { // Покидаем точку и становимся на дорогу к следующей точке
	currentPathIndex++;
	Point* nextPoint = path[currentPathIndex];
	this->setLocationState(ON_ROAD);
	this->setVehicleRoad(findConnection(this->currentPointId, nextPoint->getPointId()));
	this->ticksRemaining = findConnection(this->currentPointId, nextPoint->getPointId())->getTicksToTraverse();

}

void Vehicle::onArrivalToPoint() {
	Point* arrivedPoint = path[currentPathIndex];
	std::cout << getVehicleType() << " (id #" << this->getVehicleId() << ") arrived at point (id #" << arrivedPoint->getPointId() << "). \n";
	this->currentPointId = arrivedPoint->getPointId();
	this->ticksRemaining = 0;
	this->ticksAtCurrentPoint = 0;

	if (currentPathIndex == path.size() - 1) {
		std::cout << getVehicleType() << " (id #" << this->getVehicleId() << ") arrived at final destination - waiting\n";
		this->path.clear();
		this->currentRoad = nullptr;
		this->currentPathIndex = 0;
	}
}

bool Vehicle::canDepartFromPoint() {
	return ticksAtCurrentPoint >= 3;
}


Car::Car() {
	std::cout << "Car created using default constructor. This is definitely a bug.\n";
	movementStrategy = new StandartCarMovingStrategy();
	this->setVehiclePoint(movementStrategy->returnStartingPoint()->getPointId());
}

Car::Car(int vehicleId) : Vehicle(vehicleId, "Car") {
	this->setVehicleId(vehicleId);
	movementStrategy = new StandartCarMovingStrategy();
	this->setVehiclePoint(movementStrategy->returnStartingPoint()->getPointId());
}

Car::Car(int vehicleId, std::string vehicleType)
	: Vehicle(vehicleId, vehicleType) {
	movementStrategy = new StandartCarMovingStrategy();
	this->setVehiclePoint(movementStrategy->returnStartingPoint()->getPointId());
}

Truck::Truck() {
	std::cout << "Truck created using default constructor. This is definitely a bug.\n";
	movementStrategy = new StandartCarMovingStrategy();
	this->setVehiclePoint(movementStrategy->returnStartingPoint()->getPointId());
} // конструткор по стандарту для цілі вантажівки, можливо якийсь центр логістики

Truck::Truck(int vehicleId) : Vehicle(vehicleId, "Truck")
{
	this->setVehicleId(vehicleId);
	movementStrategy = new TruckMovingStrategy();
	this->setVehiclePoint(movementStrategy->returnStartingPoint()->getPointId());
}
Truck::Truck(int vehicleId, std::string vehicleType) : Vehicle(vehicleId, vehicleType) {
	movementStrategy = new StandartCarMovingStrategy();
	this->setVehiclePoint(movementStrategy->returnStartingPoint()->getPointId());
}



SchoolBus::SchoolBus(int vehicleId) : Vehicle(vehicleId, "SchoolBus") {
	this->setVehicleId(vehicleId);
	movementStrategy = new SchoolBusMovingStrategy();
	this->setVehiclePoint(movementStrategy->returnStartingPoint()->getPointId());
}
