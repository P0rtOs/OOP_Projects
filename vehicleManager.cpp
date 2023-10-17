#include "vehicleManager.h"
#include "vehicleClass.h"

void VehicleManager::addVehicle(const std::string& make, const std::string& model) {
    vehicles.push_back(Vehicle(make, model));
}

void VehicleManager::addVehicle(const std::string& make, const std::string& model) {
    vehicles.push_back(Vehicle(make, model));
}

void VehicleManager::removeVehicle(int index) {
    if (index >= 0 && index < vehicles.size()) {
        vehicles.erase(vehicles.begin() + index);
    }
}

void VehicleManager::printVehicles() {
    for (int i = 0; i < vehicles.size(); ++i) {
        std::cout << "Vehicle " << i << ": " << vehicles[i].make << " " << vehicles[i].model << std::endl;
    }
}