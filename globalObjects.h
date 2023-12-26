#pragma once
#ifndef GLOBAL_OBJECTS_H
#define GLOBAL_OBJECTS_H

#include "pointFactory.h"
#include "vehicleFactory.h"
#include "vehicleManager.h"
#include "pointManager.h"

extern PointFactory globalPointFactory;
extern PointManager globalPointManager;
extern VehicleFactory globalVehicleFactory;
extern VehicleManager globalVehicleManager;

#endif // GLOBAL_OBJECTS_H
