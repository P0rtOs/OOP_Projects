#include "Manager.h"
#include "tickerClass.h"
#include "globalObjects.h"
#include <conio.h>
#include <chrono>
#include <thread>


// TODO: ����������� ��������� UML ��������, ��� ������ ������ ����� ������, �� ����������� ��������� (���������) ���������� �������. �� ��� ��� �� ������� ��� ������ Manager ���� �� ����� ������ main

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


// ����� ��� ������� ��������� ����
void Manager::startTestSimulation()
{
    // TODO: ������� ������ ���� � �������� ����������, ���������������� ���� ����������, ������� ������ ��������
    Ticker ticker;

    Point* point1 = globalPointFactory.createPoint(1, 2, 3);
    Point* point2 = globalPointFactory.createPoint(2, 4, 5);

    globalPointManager.addPoint(point1);

    // ��������� ������������� ������ �� ��������� ������ addVehicle
    Point *startPoint = new Point(1, 2, 3);
    Point *endPoint = new Point(4, 5, 6);

    Vehicle* car = globalVehicleFactory.createVehicle(1, "Car");
    Vehicle* truck = globalVehicleFactory.createVehicle(1, "Truck");

    globalVehicleManager.addVehicle(car);
    globalVehicleManager.addVehicle(truck);

    ticker.registerObserver(car);
    ticker.registerObserver(truck);


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

    // TODO: ������� ������ - ���� ��� ���������, ���� �������
    ticker.unregisterObserver(car);
    ticker.unregisterObserver(truck);
    globalVehicleManager.removeVehicle(car);
    globalVehicleManager.removeVehicle(truck);
    delete car;
    delete truck;
    globalPointManager.removePoint(point1->getPointId());
    globalPointManager.removePoint(point2->getPointId());

    delete point1;
    delete point2;

}

// ����� ��� ���������� ���� ������������ ������

// ����� ��� ���������� ���������
void Manager::endSimulation()
{
    // TODO: ����� ��� ���������� ���������
}