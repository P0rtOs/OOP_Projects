#include <iostream>
#include "Manager.h"
// GlobalObjects.cpp
#include "GlobalObjects.h"



int main()
{
    Manager test;
    PointFactory globalPointFactory; // The actual instance
    PointManager globalPointManager;
    VehicleFactory globalVehicleFactory;
    VehicleManager globalVehicleManager;
    test.startTestSimulation();
    
}