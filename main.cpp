#include <iostream>
#include "Manager.h"
// GlobalObjects.cpp
#include "GlobalObjects.h"


int main()
{

    PointFactory globalPointFactory; // The actual instance
    PointManager globalPointManager;
    VehicleFactory globalVehicleFactory;
    VehicleManager globalVehicleManager;
    Manager test;
    test.startTestSimulation();
    
}