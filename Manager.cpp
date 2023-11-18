#include "Manager.h"

Manager::Manager() {
    std::cout << "Manager created. " << std::endl;
}

Manager::~Manager() {
    std::cout << "Manager deleated. " << std::endl;
}

// Метод для розрахунку маршруту кожним окремим транспортним засобом
void Manager::planRoute(Vehicle vehicle, const Point destination, const std::vector<Point> stops)
{
    // Логіка для планування маршруту
}

// Метод для запуску симуляції руху
void Manager::startTestSimulation() {
    VehicleManager* manager = new VehicleManager(); // Створення об'єкта класу VehicleManager

    // Додавання транспортного засобу за допомогою методу addVehicle
    Point* startPoint = new Point(1, 2, 3);
    Point* endPoint = new Point(4, 5, 6);

    manager->addVehicle(1, startPoint->getPointId(), endPoint->getPointId(), "test");
   // }

        std::cout << "all DONE" << std::endl << std::endl;

    manager->printVehiclesList();

    delete startPoint;
    delete endPoint;
    delete manager;
    
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