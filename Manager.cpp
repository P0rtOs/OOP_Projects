#include "Manager.h"
#include "globalObjects.h"
#include <chrono>
#include <thread>

void Manager::run()
{
    running = true;
    while (running) {
        ticker.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

void Manager::startSimulation()
{
    if (!isRunning()) {
        for (auto& vehicle : globalVehicleManager.getVehicles()) {
            ticker.registerObserver(vehicle);
        }

        start();
    }
}

void Manager::endSimulation()
{
    running = false;
    wait(); // Wait for the thread to finish

    // Unregister observers
    for (auto& vehicle : globalVehicleManager.getVehicles()) {
        ticker.unregisterObserver(vehicle);
    }

    std::cout << "Simulation ended. All vehicles have been unregistered." << std::endl;
}


Ticker& Manager::getTicker()
{
    return ticker;
}

void Manager::setSimulationSpeed(int speed)
{
    interval = 1000 / speed;
}