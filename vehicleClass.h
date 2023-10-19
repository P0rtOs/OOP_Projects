#pragma once
#include <iostream>
#include "roadClass.h"

class Vehicle {
	private:
		int vehicleId;
		Road vehicleRoad;
		std::string vehicleType;
	

	public:
		Vehicle();
		Vehicle(int vehicleId, Road vehicleRoad, std::string vehicleType);
		~Vehicle();
		int getVehicleId();
		Road getVehicleRoad();
		void setVehicleId(int Id);
		void setVehicleRoad(Road thisRoad);
		void setVehicleType(std::string vehicleType);
		std::string getVehicleType();

};

