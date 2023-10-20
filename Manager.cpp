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

    Road* testingRoad = new Road(*startPoint, *endPoint, 4);
    int i = 0;

    //for (i; i <= 5; i++) {
        manager->addVehicle(i, *testingRoad, "test");
   // }



    manager->printVehiclesList();

    delete startPoint;
    delete endPoint;
    delete testingRoad;
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