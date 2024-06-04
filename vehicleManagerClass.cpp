#include "vehicleManagerClass.h"
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
        vehicles.erase(it); // First erase from the vector
        delete vehicle; // Then delete the vehicle
    }
}

Vehicle* VehicleManager::getVehicle(int id) {
    for (Vehicle* vehicle : vehicles) {
        if (vehicle->getVehicleId() == id) {
            return vehicle;
        }
    }
    return nullptr;  // Return nullptr if no vehicle with the given ID is found
}

std::vector<Vehicle*>& VehicleManager::getVehicles() {
    return vehicles;
}


// TODO: Продумать как очищать память машин и точек, что еще должен делать менеджер машин? 