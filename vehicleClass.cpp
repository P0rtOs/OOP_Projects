#include <iostream>

#include "vehicleClass.h"
#include "globalObjects.h"
#include <string>
#include <algorithm>

// TODO: ƒопустим у нас машина будет спанитьс€ на точке и ждать. ѕо прошествию рандомного количества тиков, 
// movementStrategy должна дать ей конечную точку, к которой она будет ехать алгоритмом (каким еще надо подумать, возможно тоже рандом) 
// ѕо пришествию на точку, она должна стать и рандомно ждать следующих указаний.

Connection* findConnection(int pointAId, int pointBId) {
	Point* pointA = globalPointManager.getPoint(pointAId);
	Point* pointB = globalPointManager.getPoint(pointBId);

	if (!pointA || !pointB) {
		return nullptr;  // One or both points not found
	}

	for (Connection* conn : pointA->getNeighbors()) {
		if (conn && conn->getNeighborId() == pointBId) {
			return const_cast<Connection*>(conn);
		}
	}

	return nullptr;  // No connection found
}

Vehicle::Vehicle() : currentState(AT_POINT), currentPointId(0)
{
	std::cout << "Vehicle created using default constuctor. " << std::endl;
}
Vehicle::Vehicle(int vehicleId, std::string vehicleType) : currentState(AT_POINT)
{
	this->setVehicleId(vehicleId);
	this->setVehicleType(vehicleType);

	std::cout << "Vehicle created with following parameters: " << this->getVehicleId() << " " << this->getVehicleType() << std::endl;
}
Vehicle::~Vehicle() {std::cout << "Vehicle deleted" << std::endl;}

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
		locationInfo = "Vehicle " + std::to_string(getVehicleId()) + " at point ID " + std::to_string(currentPointId);
	}
	else if (currentState == ON_ROAD) {
		locationInfo = "Vehicle " + std::to_string(getVehicleId()) + " moving to point ID " + std::to_string(currentRoad->getNeighborId()) + " Remaining ticks : " + std::to_string(ticksRemaining);
	}
	return locationInfo;
}

void Vehicle::update() {
	if (!path.empty() && currentPathIndex < path.size()) {
		// If the vehicle is currently at a point, check if it can move to the next road
		if (currentState == AT_POINT) {
			ticksAtCurrentPoint++;
			// Logic to decide if the vehicle can start moving on the next road
			// For example, you might check if enough ticks have passed
			if (canDepartFromPoint()) {
				moveToNextPointOnPath(); // Move to the next road or point
			}
		}
		else if (currentState == ON_ROAD) {
			// If the vehicle is currently on a road, update its progress along the road
			// Decrement the ticks remaining to traverse the current road
			--ticksRemaining;
			if (ticksRemaining <= 0) {
				// The vehicle has reached the next point
				currentState = AT_POINT; // Update the state to AT_POINT
				// Possibly perform some actions upon arriving at the point
				onArrivalToPoint();
			}
		}
	}
	else if (path.empty()) {
		std::cout << "Path empty - finding new path" << std::endl;
		if (movementStrategy != nullptr) {
			Point* destination = movementStrategy->returnRandomDestination(this->getCurrentPointId());
			if (destination != nullptr) {
				movementStrategy->dijkstraShortestPath(this->getCurrentPointId(), destination->getPointId(), *this);
				std::cout << "Passed fucking bullshit\n";
			}
			else {
				std::cerr << "No destination found\n";
				// Handle the case when no valid destination is found
				// For example, log an error, throw an exception, or take some default action
			}
		}
		else {
			std::cerr << "Error: movementStrategy is null.\n";
			// Handle the null case
		}
	}
}
void Vehicle::moveToNextPointOnPath() { // ѕокидаем точку и становимс€ на дорогу к следующей точке
	currentPathIndex++;
	Point* nextPoint = path[currentPathIndex];
	this->setLocationState(ON_ROAD);
	this->setVehicleRoad(findConnection(this->currentPointId, nextPoint->getPointId()));
	ticksRemaining = findConnection(this->currentPointId, nextPoint->getPointId())->getTicksToTraverse();

}
void Vehicle::onArrivalToPoint() {
	// Perform actions that should occur when a vehicle arrives at a point
	// Example: Update vehicle's current point, possibly wait for loading/unloading
	Point* arrivedPoint = path[currentPathIndex];
	std::cout << "Vehicle arrived at point ID: " << arrivedPoint->getPointId() << std::endl;
	// Set the new current point for the vehicle
	currentPointId = arrivedPoint->getPointId();
	// Reset ticks remaining since we've arrived at the point
	ticksRemaining = 0;
	ticksAtCurrentPoint = 0;
	// If there's a next point, prepare to move to the next road

	if(currentPathIndex == path.size() - 1) {
		// If this was the last point, perform any completion logic here
		std::cout << "Arrived at destination - waiting for further commands\n";
		path.clear();
		currentRoad = nullptr;
		currentPathIndex = 0;
	}
}
bool Vehicle::canDepartFromPoint() {
	return ticksAtCurrentPoint >= 3;
}

Car::Car() : numberOfDoors(4) {
	movementStrategy = new StandartCarMovingStrategy();
}
Car::Car(int vehicleId){
	this->setVehicleId(vehicleId);
	movementStrategy = new StandartCarMovingStrategy();
}
Car::Car(int vehicleId, std::string vehicleType, int doors)
	: Vehicle(vehicleId, vehicleType), numberOfDoors(doors) {
	movementStrategy = new StandartCarMovingStrategy();
}

int Car::getNumberOfDoors()
{
	return numberOfDoors;
}
void Car::setNumberOfDoors(int doors)
{
	numberOfDoors = doors;
}

Truck::Truck() {
	movementStrategy = new StandartCarMovingStrategy();
} // конструткор по стандарту дл€ ц≥л≥ вантаж≥вки, можливо €кийсь центр лог≥стики
Truck::Truck(int vehicleId)
{
	this->setVehicleId(vehicleId);
	movementStrategy = new StandartCarMovingStrategy();
}
Truck::Truck(int vehicleId, std::string vehicleType) : Vehicle(vehicleId, vehicleType) {
	movementStrategy = new StandartCarMovingStrategy();
}
