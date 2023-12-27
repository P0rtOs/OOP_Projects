#include "Manager.h"
#include "tickerClass.h"
#include "globalObjects.h"
#include <conio.h>
#include <chrono>
#include <thread>
#include "fileManager.h"

// TODO: Реализовать примерную UML диаграму, что должен каждый класс делать, по возможности упростить (уменьшить) количество классов. До сих пор не понимаю что делает Manager чего не может делать main

bool userPressedStopButton() {
    if (_kbhit()) {  // Check if a key has been pressed
        char ch = _getch();  // Get the pressed key
        return ch == 'q' || ch == 'Q';  // Check if the key is 'q' or 'Q'
    }
    return false;  // Return false if no key has been pressed
}



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
    //readingFiles testRead;

    //testRead.readPointsFromFile("lox");
    //testRead.readPointsFromFile("zavtra");
    // TODO: Вписать тиккер клас в менеджер приложения, зарегистрировать всех обсерверов, которые должны тикаться
    Ticker ticker;

    Point* point0 = globalPointFactory.createPoint(0, 2, 3);
    Point* point1 = globalPointFactory.createPoint(1, 4, 5);
    Point* point2 = globalPointFactory.createPoint(2, 6, 3);
    Point* point3 = globalPointFactory.createPoint(3, 8, 7);

    globalPointManager.addPoint(point0);
    globalPointManager.addPoint(point1);
    globalPointManager.addPoint(point2);
    globalPointManager.addPoint(point3);

    point0->addNeighbor(1, 6, 40);
    point0->addNeighbor(2, 8, 40);
    point1->addNeighbor(3, 7, 40);
    point2->addNeighbor(3, 8, 40);


    globalPointManager.addPoint(point1);

    // Додавання транспортного засобу за допомогою методу addVehicle
    Vehicle* car = globalVehicleFactory.createVehicle(0, "Car");
    Vehicle* truck = globalVehicleFactory.createVehicle(1, "Truck");

    globalVehicleManager.addVehicle(car);
    globalVehicleManager.addVehicle(truck);

    ticker.registerObserver(car);
    ticker.registerObserver(truck);

    /*std::cout << car->getCurrentPointId();
    std::cout << truck->getCurrentPointId();*/

    while (true) {
        ticker.tick();  // Perform a simulation tick
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (userPressedStopButton()) {
            break;  // Exit the loop if the user pressed 'q'
        }
    }
    // }

    std::cout << "all DONE" << std::endl
              << std::endl;

    // TODO: Очистка памяти - нету для менеджера, надо создать
    ticker.unregisterObserver(car);
    ticker.unregisterObserver(truck);
    globalVehicleManager.removeVehicle(car);
    globalVehicleManager.removeVehicle(truck);
    globalPointManager.removePoint(point0->getPointId());
    globalPointManager.removePoint(point1->getPointId());
    globalPointManager.removePoint(point2->getPointId());
    globalPointManager.removePoint(point3->getPointId());

}

// Метод для відстеження руху транспортних засобів

// Метод для завершення симуляції
void Manager::endSimulation()
{
    // TODO: Логіка для завершення симуляції
}