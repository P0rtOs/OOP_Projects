#pragma once
#include <vector>
#include "vehicleClass.h"

class VehicleManager {
private:
    std::vector<Vehicle*> vehicles;

public:
    void addVehicle(Vehicle* vehicle);
    void removeVehicle(Vehicle* vehicle);
};
