#pragma once
#include <iostream>
#include <vector>
#include "vehicleClass.h"

class VehicleManager {
    public:
        VehicleManager() = default;
        ~VehicleManager() = default;
        void addVehicle(int id, Road road, std::string type);
        void removeVehicle(int index);
        void printVehiclesList();


    private:
        std::vector<Vehicle> vehicles;
};

