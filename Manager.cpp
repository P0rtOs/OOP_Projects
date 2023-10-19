#include "Manager.h"

Manager::Manager() {
    std::cout << "Manager created" << std::endl;
}

Manager::~Manager() {
    std::cout << "Manager deleated" << std::endl;
}

// Метод для розрахунку маршруту кожним окремим транспортним засобом
void Manager::planRoute(Vehicle vehicle, const Point destination, const std::vector<Point> stops)
{
    // Логіка для планування маршруту
}

// Метод для запуску симуляції руху
void Manager::startTestSimulation() {
    VehicleManager manager; // Створення об'єкта класу VehicleManager

    // Додавання транспортного засобу за допомогою методу addVehicle
    Point testingPoint(1, 2, 3);
    Road testingRoad(testingPoint, testingPoint, 4);
    int i = 0;

    for (i; i <= 5; i++) {
        manager.addVehicle(i, testingRoad, "test");
    }

    manager.printVehiclesList();
}


// Метод для відстеження руху транспортних засобів
void Manager::trackVehicleMovement() //метод для запису переміщень в файл, чи чогось подібного.
{
    // Логіка для відстеження руху
}

// Метод для завершення симуляції
void Manager::endSimulation()
{
    // Логіка для завершення симуляції
}