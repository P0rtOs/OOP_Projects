#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "vehicleClass.h"

class VehicleManager {
    public:
        VehicleManager() = default;
        ~VehicleManager() = default;
        void addVehicle(int id, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string type);
        void removeVehicle(int index);
        void printVehiclesList();


    private:
        std::vector<Vehicle> vehicles;
};

