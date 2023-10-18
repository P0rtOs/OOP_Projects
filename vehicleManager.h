#pragma once
#include <iostream>
#include <vector>
#include "vehicleClass.h"

class VehicleManager {
    public:
        VehicleManager();
        ~VehicleManager();
        void addVehicle(int id, Road road, std::string type);
        void removeVehicle(int index);
        void printVehiclesList();


    private:
        std::vector<Vehicle> vehicles;
};

