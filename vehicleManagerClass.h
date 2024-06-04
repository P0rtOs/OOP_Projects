#pragma once
#include <vector>
#include "vehicleClass.h"

class VehicleManager {
private:
    std::vector<Vehicle*> vehicles;

public:
    ~VehicleManager();
    void addVehicle(Vehicle* vehicle);
    void removeVehicle(Vehicle* vehicle);
    Vehicle* getVehicle(int id);
    std::vector<Vehicle*>& getVehicles();
};
