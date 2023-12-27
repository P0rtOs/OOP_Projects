#include "vehicleManager.h"
#include <algorithm>

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


// TODO: ��������� ��� ������� ������ ����� � �����, ��� ��� ������ ������ �������� �����? 