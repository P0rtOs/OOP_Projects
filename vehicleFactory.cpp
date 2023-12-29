#include "vehicleFactory.h"
#include "vehicleClass.h"

Vehicle* VehicleFactory::createVehicle(int id, std::string type) {
    if (type == "Car") {
        return new Car(id);
    }
    else if (type == "Truck") {
        return new Truck(id);
    }
    else if (type == "SchoolBus") {
        return new SchoolBus(id);
    }
    else {
        return new Car(id);
    }
    /*else if (type == "SchoolBus") {
        return new SchoolBus();
    }*/
}

