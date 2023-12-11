#include "Manager.h"
#include "vehicleFactory.h"
#include "vehicleManager.h"
#include "pointFactory.h"
#include "pointManager.h"

// TODO: ����������� ��������� UML ��������, ��� ������ ������ ����� ������, �� ����������� ��������� (���������) ���������� �������. �� ��� ��� �� ������� ��� ������ Manager ���� �� ����� ������ main


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
    VehicleManager vehicleManager;
    VehicleFactory vehicleFactory;
    PointFactory pointFactory;
    PointManager pointManager;

    Point* point1 = pointFactory.createPoint(1, 2, 3);
    Point* point2 = pointFactory.createPoint(2, 4, 5);

    pointManager.addPoint(point1);

    // ��������� ������������� ������ �� ��������� ������ addVehicle
    Point *startPoint = new Point(1, 2, 3);
    Point *endPoint = new Point(4, 5, 6);

    Vehicle* car = vehicleFactory.createVehicle(1, "Car");
    Vehicle* truck = vehicleFactory.createVehicle(1, "Truck");

    vehicleManager.addVehicle(car);
    vehicleManager.addVehicle(truck);
    // }

    std::cout << "all DONE" << std::endl
              << std::endl;

    // TODO: ������� ������ - ���� ��� ���������, ���� �������
}

// ����� ��� ���������� ���� ������������ ������

// ����� ��� ���������� ���������
void Manager::endSimulation()
{
    // TODO: ����� ��� ���������� ���������
}