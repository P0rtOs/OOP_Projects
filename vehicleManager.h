#pragma once
#include <iostream>
#include <vector>
#include "vehicleClass.h"

class VehicleManager {
    public:
        VehicleManager();
        ~VehicleManager();
        void addVehicle(const std::string& make, const std::string& model);
        void removeVehicle(int index);
        void printVehicles();


    private:
        //std::vector<> vehicles;
};

