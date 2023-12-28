#include "Manager.h"
#include "tickerClass.h"
#include "globalObjects.h"
#include "fileManager.h"

#include <conio.h>
#include <chrono>
#include <thread>



bool userPressedStopButton() {
    if (_kbhit()) {  // Check if a key has been pressed
        char ch = _getch();  // Get the pressed key
        return ch == 'q' || ch == 'Q';  // Check if the key is 'q' or 'Q'
    }
    return false;  // Return false if no key has been pressed
}

// Метод для запуску симуляції руху
void Manager::startTestSimulation()
{


    readingInterface.readPointsFromFile("lox");

    /*auto point0 = globalPointFactory.createPoint(0, 2, 3);
    auto point1 = globalPointFactory.createPoint(1, 4, 5);
    auto point2 = globalPointFactory.createPoint(2, 6, 3);
    auto point3 = globalPointFactory.createPoint(3, 8, 7);

    globalPointManager.addPoint(move(point0));
    globalPointManager.addPoint(move(point1));
    globalPointManager.addPoint(move(point2));
    globalPointManager.addPoint(move(point3));

    Point* p0 = globalPointManager.getPoint(0);
    Point* p1 = globalPointManager.getPoint(1);
    Point* p2 = globalPointManager.getPoint(2);
    Point* p3 = globalPointManager.getPoint(3);

    if (p0) p0->addNeighbor(1, 6, 40);
    if (p0) p0->addNeighbor(2, 8, 40);
    if (p1) p1->addNeighbor(3, 7, 40);
    if (p2) p2->addNeighbor(3, 8, 40);*/


    Vehicle* car = globalVehicleFactory.createVehicle(0, "Car");
    Vehicle* truck = globalVehicleFactory.createVehicle(1, "Truck");
    Vehicle* schoolbus = globalVehicleFactory.createVehicle(2, "SchoolBus");

    globalVehicleManager.addVehicle(car);
    globalVehicleManager.addVehicle(truck);
    globalVehicleManager.addVehicle(schoolbus);

    ticker.registerObserver(car);
    ticker.registerObserver(truck);
    ticker.registerObserver(schoolbus);


    while (true) {
        ticker.tick();  // Perform a simulation tick
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (userPressedStopButton()) {
            break;
        }
    }
    // }

    std::cout << "User entered exit sequence. Wrapping up..." << std::endl
              << std::endl;

    endSimulation();
}

// Метод для завершення симуляції
void Manager::endSimulation()
{
    // Iterate through all vehicles and unregister them
    for (auto& vehicle : globalVehicleManager.getVehicles()) {
        ticker.unregisterObserver(vehicle);
    }

    std::cout << "Simulation ended. All vehicles have been unregistered." << std::endl;
}