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
	void Vehicle::setVehiclePoint(int newPointId) { currentPointId = newPointId; }
	void Vehicle::setVehicleRoad(Connection* newConnection) { currentRoad = newConnection; }
	//void Vehicle::setVehicleGoalPoint(int newGoalPointId) { goalPointId = newGoalPointId; }
	void Vehicle::setMovementStrategyPM(PointManager* pm) {
		movementStrategy = new StandartCarMovingStrategy(pm);
	}
	void Vehicle::setPath(const std::vector<Point*>& newPath) {
		path = newPath;
		currentPathIndex = 0;
	}
	//void Vehicle::moveToRoad(const Connection& road) {
	/*	currentState = ON_ROAD;
		currentRoad = road;
	}*/
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
			locationInfo = "Vehicle is on road to point ID " + std::to_string(currentRoad->getNeighborId());
		}
		return locationInfo;
	}

	void Vehicle::update() {
		if (!path.empty() && currentPathIndex < path.size()) {
			// If the vehicle is currently at a point, check if it can move to the next road
			if (currentState == AT_POINT) {
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
		if (path.empty()) {
			std::cout << "Path empty - no actions taken" << std::endl;
		}
	}

	void Vehicle::moveToNextPointOnPath() {
		Point* nextPoint = path[currentPathIndex];
		currentPathIndex++;
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
		if (currentPathIndex < path.size() - 1) {
			// Prepare for the next road, but don't move yet - wait for the next update tick
			Point* nextPoint = path[currentPathIndex + 1];
			// Find the connection (road) to the next point
			Connection* nextRoad = nullptr;
			for (auto* connection : movementStrategy->pointManager->getPoint(currentPointId)->getNeighbor()) {
				if (connection->getNeighborId() == nextPoint->getPointId()) {
					nextRoad = connection;
					break;
				}
			}
			if (nextRoad) {
				// Prepare for the next road
				currentRoad = nextRoad; // Set the next road
				ticksRemaining = nextRoad->getTicksToTraverse(); // Set the travel time
				// The vehicle is now ready to move onto this road in the next update cycle
			}
		}
		else {
			// If this was the last point, perform any completion logic here
		}
	}

	bool Vehicle::canDepartFromPoint() {
		return ticksAtCurrentPoint >= 3;
	}

	Car::Car() : numberOfDoors(4) {}
	Car::Car(int vehicleId, std::string vehicleType, int doors, PointManager* pm)
		: Vehicle(vehicleId, vehicleType), numberOfDoors(doors) {
		setMovementStrategyPM(pm);
	}
	int Car::getNumberOfDoors()
	{
		return numberOfDoors;
	}
	void Car::setNumberOfDoors(int doors)
	{
		numberOfDoors = doors;
	}

	Truck::Truck() : aim(default_point) {} // конструткор по стандарту дл€ ц≥л≥ вантаж≥вки, можливо €кийсь центр лог≥стики
	Truck::Truck(int vehicleId, std::string vehicleType, PointManager* pm)
		: Vehicle(vehicleId, vehicleType) {}
	Point Truck::getAim()
	{
		return aim;
	}
	void Truck::setAim(Point point)
	{
		aim = point;
	}
	//SchoolBus::SchoolBus() : bus_stations_to_serve(default_vector), school_to_serve(default_point) {}
	//
	//SchoolBus::SchoolBus(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point school_to_serve1, std::vector<Point> bus_stations_to_serve1)
	//	: Vehicle(vehicleId, newVehicleCurrentPointId, newVehicleGoalPoint, vehicleType), school_to_serve(school_to_serve1), bus_stations_to_serve(bus_stations_to_serve1) {}
	//
	//Point SchoolBus::getSchool()
	//{
	//	return school_to_serve;
	//}
	//
	//void SchoolBus::setSchool(Point school_to_serve1)
	//{
	//	school_to_serve = school_to_serve1;
	//}
	//
	//std::vector<Point> SchoolBus::getbus_stations_to_serve()
	//{
	//	return bus_stations_to_serve;
	//}
	//
	//void SchoolBus::setbus_stations_to_serve(std::vector<Point> bus_stations_to_serve1)
	//{
	//	bus_stations_to_serve = bus_stations_to_serve1;
	//}