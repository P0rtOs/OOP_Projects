#pragma once
#include "vehicleClass.h"

class Vehicle;

class MovementStrategy {
protected:
	
public:
	MovementStrategy();
	virtual void move(Vehicle& vehicle) = 0;
	virtual vector<Point*> dijkstraShortestPath(int sourceId, int targetId, Vehicle& vehicle) = 0;
	virtual Point* returnRandomDestination(int currentPointId) = 0;
	virtual std::string returnStrategyType() = 0;;
};

class StandartCarMovingStrategy : public MovementStrategy {
public:
	StandartCarMovingStrategy();
	std::string returnStrategyType() override;
	vector<Point*> dijkstraShortestPath(int sourceId,int targetId, Vehicle& vehicle) override;
	void move(Vehicle& vehicle) override;
	Point* returnRandomDestination(int currentPointId) override;
};


// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  