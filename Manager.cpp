#include "Manager.h"
#include "vehicleFactory.h"

// TODO: Реализовать примерную UML диаграму, что должен каждый класс делать, по возможности упростить (уменьшить) количество классов. До сих пор не понимаю что делает Manager чего не может делать main


Manager::Manager()
{
    std::cout << "Manager created. " << std::endl;
}

Manager::~Manager()
{
    std::cout << "Manager deleted. " << std::endl;
}

// Метод для розрахунку маршруту кожним окремим транспортним засобом
void Manager::planRoute(Vehicle vehicle, const Point destination, const std::vector<Point> stops)
{
    // Логіка для планування маршруту
}

// Метод для запуску симуляції руху
void Manager::startTestSimulation()
{

    // TODO: Вписать тиккер клас в менеджер приложения, зарегистрировать всех обсерверов, которые должны тикаться
    VehicleManager manager;
    VehicleFactory factory;

    // Додавання транспортного засобу за допомогою методу addVehicle
    Point *startPoint = new Point(1, 2, 3);
    Point *endPoint = new Point(4, 5, 6);

    Vehicle* car = factory.createVehicle(1, "Car");
    Vehicle* truck = factory.createVehicle(1, "Truck");

    manager.addVehicle(car);
    manager.addVehicle(truck);
    // }

    std::cout << "all DONE" << std::endl
              << std::endl;

    // TODO: Очистка памяти - нету для менеджера, надо создать
}

// Метод для відстеження руху транспортних засобів
void Manager::trackVehicleMovement() // метод для запису переміщень в файл, чи чогось подібного.
{
    // TODO: Логіка для відстеження руху
}

// Метод для завершення симуляції
void Manager::endSimulation()
{
    // TODO: Логіка для завершення симуляції
}