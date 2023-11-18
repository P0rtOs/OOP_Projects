#include "Manager.h"

Manager::Manager() {
    std::cout << "Manager created. " << std::endl;
}

Manager::~Manager() {
    std::cout << "Manager deleated. " << std::endl;
}

// ����� ��� ���������� �������� ������ ������� ������������ �������
void Manager::planRoute(Vehicle vehicle, const Point destination, const std::vector<Point> stops)
{
    // ����� ��� ���������� ��������
}

// ����� ��� ������� ��������� ����
void Manager::startTestSimulation() {
    VehicleManager* manager = new VehicleManager(); // ��������� ��'���� ����� VehicleManager

    // ��������� ������������� ������ �� ��������� ������ addVehicle
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


// ����� ��� ���������� ���� ������������ ������
void Manager::trackVehicleMovement() //����� ��� ������ ��������� � ����, �� ������ ��������.
{
    // ����� ��� ���������� ����
}

// ����� ��� ���������� ���������
void Manager::endSimulation()
{
    // ����� ��� ���������� ���������
}