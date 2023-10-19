#include "Manager.h"

Manager::Manager() {
    std::cout << "Manager created" << std::endl;
}

Manager::~Manager() {
    std::cout << "Manager deleated" << std::endl;
}

// ����� ��� ���������� �������� ������ ������� ������������ �������
void Manager::planRoute(Vehicle vehicle, const Point destination, const std::vector<Point> stops)
{
    // ����� ��� ���������� ��������
}

// ����� ��� ������� ��������� ����
void Manager::startTestSimulation() {
    VehicleManager manager; // ��������� ��'���� ����� VehicleManager

    // ��������� ������������� ������ �� ��������� ������ addVehicle
    Point testingPoint(1, 2, 3);
    Road testingRoad(testingPoint, testingPoint, 4);
    int i = 0;

    for (i; i <= 5; i++) {
        manager.addVehicle(i, testingRoad, "test");
    }

    manager.printVehiclesList();
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