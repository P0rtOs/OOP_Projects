#pragma once
#include "vehicleManager.h"

class Manager
{
    public:
        Manager();
        ~Manager();
        void planRoute(Vehicle vehicle, const Point destination, const std::vector<Point> stops);
        void startTestSimulation();
        void trackVehicleMovement();
        void endSimulation();
};