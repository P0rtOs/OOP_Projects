#include "Manager.h"
#include "vehicleFactory.h"

// TODO: ����������� ��������� UML ��������, ��� ������ ������ ����� ������, �� ����������� ��������� (���������) ���������� �������. �� ��� ��� �� ������� ��� ������ Manager ���� �� ����� ������ main


Manager::Manager()
{
    std::cout << "Manager created. " << std::endl;
}

Manager::~Manager()
{
    std::cout << "Manager deleted. " << std::endl;
}

// ����� ��� ���������� �������� ������ ������� ������������ �������
void Manager::planRoute(Vehicle vehicle, const Point destination, const std::vector<Point> stops)
{
    // ����� ��� ���������� ��������
}

// ����� ��� ������� ��������� ����
void Manager::startTestSimulation()
{

    // TODO: ������� ������ ���� � �������� ����������, ���������������� ���� ����������, ������� ������ ��������
    VehicleManager manager;
    VehicleFactory factory;

    // ��������� ������������� ������ �� ��������� ������ addVehicle
    Point *startPoint = new Point(1, 2, 3);
    Point *endPoint = new Point(4, 5, 6);

    Vehicle* car = factory.createVehicle(1, "Car");
    Vehicle* truck = factory.createVehicle(1, "Truck");

    manager.addVehicle(car);
    manager.addVehicle(truck);
    // }

    std::cout << "all DONE" << std::endl
              << std::endl;

    // TODO: ������� ������ - ���� ��� ���������, ���� �������
}

// ����� ��� ���������� ���� ������������ ������
void Manager::trackVehicleMovement() // ����� ��� ������ ��������� � ����, �� ������ ��������.
{
    // TODO: ����� ��� ���������� ����
}

// ����� ��� ���������� ���������
void Manager::endSimulation()
{
    // TODO: ����� ��� ���������� ���������
}