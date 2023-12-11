#include "Manager.h"
#include "vehicleFactory.h"
#include "vehicleManager.h"
#include "pointFactory.h"
#include "pointManager.h"

// TODO: Реализовать примерную UML диаграму, что должен каждый класс делать, по возможности упростить (уменьшить) количество классов. До сих пор не понимаю что делает Manager чего не может делать main


Manager::Manager()
{
    std::cout << "Manager created. " << std::endl;
}

Manager::~Manager()
{
    std::cout << "Manager deleted. " << std::endl;
}


// Метод для запуску симуляції руху
void Manager::startTestSimulation()
{

    // TODO: Вписать тиккер клас в менеджер приложения, зарегистрировать всех обсерверов, которые должны тикаться
    VehicleManager vehicleManager;
    VehicleFactory vehicleFactory;
    PointFactory pointFactory;
    PointManager pointManager;

    Point* point1 = pointFactory.createPoint(1, 2, 3);
    Point* point2 = pointFactory.createPoint(2, 4, 5);

    pointManager.addPoint(point1);

    // Додавання транспортного засобу за допомогою методу addVehicle
    Point *startPoint = new Point(1, 2, 3);
    Point *endPoint = new Point(4, 5, 6);

    Vehicle* car = vehicleFactory.createVehicle(1, "Car");
    Vehicle* truck = vehicleFactory.createVehicle(1, "Truck");

    vehicleManager.addVehicle(car);
    vehicleManager.addVehicle(truck);
    // }

    std::cout << "all DONE" << std::endl
              << std::endl;

    // TODO: Очистка памяти - нету для менеджера, надо создать
}

// Метод для відстеження руху транспортних засобів

// Метод для завершення симуляції
void Manager::endSimulation()
{
    // TODO: Логіка для завершення симуляції
}