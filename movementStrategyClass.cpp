#include "movementStrategyClass.h"



void StandartCarMovingStrategy::move(Vehicle& vehicle) {
	std::cout << "Moving car" << vehicle.getVehicleId() << std::endl;
}

// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  