#pragma once
#include "vehicleClass.h"

class MovementStrategy {
public:
	virtual void move(Vehicle& vehicle) = 0;
};

class StandartCarMovingStrategy : public MovementStrategy {
public:
	void move(Vehicle& vehicle) override;
};


// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  