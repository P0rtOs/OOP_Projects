#include "vehicleManager.h"

void VehicleManager::addVehicle(int id, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string type) {
    vehicles.emplace_back(id, newVehicleCurrentPointId, newVehicleGoalPoint, type);
}


void VehicleManager::removeVehicle(int id) {
    if (id >= 0 && id < vehicles.size()) {
        vehicles.erase(vehicles.begin() + id);
    }
}

void VehicleManager::printVehiclesList() {
    for (int i = 0; i < vehicles.size(); ++i) {
        std::cout << "Vehicle " << i << ": " << vehicles[i].getVehicleId() << " " << vehicles[i].getVehicleType() << std::endl;
    }
}