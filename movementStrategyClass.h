#pragma once
//#include "vehicleClass.h"
#include "pointManager.h"

class Vehicle;

class MovementStrategy {
protected:
	PointManager* pointManager;
public:
	MovementStrategy(PointManager* pm);
	virtual void move(Vehicle& vehicle) = 0;
	void setPointManager(PointManager* pm);
};

class StandartCarMovingStrategy : public MovementStrategy {
public:
	StandartCarMovingStrategy(PointManager* pm);
	void move(Vehicle& vehicle) override;
};


// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  