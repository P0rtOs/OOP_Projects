#include "vehicleManagerClass.h"
#include <algorithm>

VehicleManager::~VehicleManager() {
    std::cout << "Deleting VehicleManager instance.\n";
    for (Vehicle* vehicle : vehicles) {
        delete vehicle;
    }
    vehicles.clear();
}

void VehicleManager::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

void VehicleManager::removeVehicle(Vehicle* vehicle) {
    auto it = std::find(vehicles.begin(), vehicles.end(), vehicle);
    if (it != vehicles.end()) {
        vehicles.erase(it);
        delete vehicle;
    }
}

Vehicle* VehicleManager::getVehicle(int id) {
    for (Vehicle* vehicle : vehicles) {
        if (vehicle->getVehicleId() == id) {
            return vehicle;
        }
    }
    return nullptr;
}

std::vector<Vehicle*>& VehicleManager::getVehicles() {
    return vehicles;
}


// TODO: Продумать как очищать память машин и точек, что еще должен делать менеджер машин? 