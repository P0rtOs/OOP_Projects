#include "vehicleFactory.h"
#include "vehicleClass.h"

Vehicle* VehicleFactory::createVehicle(int id, std::string type) {
    if (type == "Car") {
        return new Car();
    }
    else if (type == "Truck") {
        return new Truck();
    }
    else {
        return new Car();
    }
    /*else if (type == "SchoolBus") {
        return new SchoolBus();
    }*/
}


// TODO:  ак должна удал€ть фабрика машини и должна ли? ¬озможно удалением машины из списка машин должен заниматьс€ менеджер, а фабрика должна лишь удал€ть сам обьект в пам€ти


//void VehicleFactory::deleteVehicle(int id) {
//    if (id >= 0 && id < vehicles.size()) {
//        vehicles.erase(vehicles.begin() + id);
//    }
//}

//void VehicleFactory::printVehiclesList() {
//    for (int i = 0; i < vehicles.size(); ++i) {
//        std::cout << "Vehicle " << i << ": " << vehicles[i].getVehicleId() << " " << vehicles[i].getVehicleType() << std::endl;
//    }
//}