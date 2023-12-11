#include <iostream>
#include "movementStrategyClass.h"


MovementStrategy::MovementStrategy(PointManager* pm) : pointManager(pm) {}

void MovementStrategy:: setPointManager(PointManager* pm) {
    pointManager = pm;
}


StandartCarMovingStrategy::StandartCarMovingStrategy(PointManager* pm) : MovementStrategy(pm) {}

void StandartCarMovingStrategy::move(Vehicle& vehicle) {
	std::cout << "Moving car" << std::endl;
}



// TODO: Написать алгоритмы как будут перемещаться разные типы машин ( стандартный, грузовик, тд )  