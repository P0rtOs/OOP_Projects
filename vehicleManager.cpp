#include "vehicleManager.h"
#include <algorithm>

VehicleManager::~VehicleManager() {
    std::cout << "Deleting VehicleManager instance.\n";
    for (Vehicle* vehicle : vehicles) {
        delete vehicle;  // Delete each dynamically allocated Vehicle
    }
    vehicles.clear();
}

void VehicleManager::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

void VehicleManager::removeVehicle(Vehicle* vehicle) {
    auto it = std::find(vehicles.begin(), vehicles.end(), vehicle);
    if (it != vehicles.end()) {
        // Optionally handle memory management, if needed
        delete* it;  // Delete the vehicle if VehicleManager owns it

        // Erase the vehicle from the vector
        vehicles.erase(it);
    }
}

std::vector<Vehicle*>& VehicleManager::getVehicles(){
    return vehicles;
}

