#pragma once
#include <iostream>
#include "pointClass.h"
#include "roadClass.h"

class Vehicle {
	private:
		int vehicleId;
		Road vehicleRoad;
		std::string vehicleType;
	

	public:
		Vehicle();
		~Vehicle();
		int getVehicleId();
		Road getVehicleRoad();
		void setVehicleRoad(Road thisRoad);
		std::string getVehicleType();

};

