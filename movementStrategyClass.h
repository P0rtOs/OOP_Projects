#pragma once
#include "vehicleClass.h"

class Vehicle;

class MovementStrategy {
protected:
	
public:
	MovementStrategy(PointManager* pm);
	virtual void move(Vehicle& vehicle) = 0;
	PointManager* pointManager;
	void setPointManager(PointManager* pm);
};

class StandartCarMovingStrategy : public MovementStrategy {
public:
	StandartCarMovingStrategy(PointManager* pm);
	vector<Point*> dijkstraShortestPath(int sourceId,int targetId, Vehicle& vehicle);
	void move(Vehicle& vehicle) override;
};


// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  