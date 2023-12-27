#pragma once
#include <iostream>
#include "pointManager.h"
#include "tickerClass.h"
#include "movementStrategyClass.h"
#include "connectionClass.h"
#include <vector>

// TODO: ��������, ������� ������ ������ ������ ��������� �� ���. 
// TODO: ����� ��� ���������� ������? ���� ���� ������� � ��� ������ bloat - �������.

// TODO: ���������� ������ ���������� ���� ������ - ��� ������ ������ movementStrategyClass, � ���� ������ ���� ����������, ������ ������ ����.
// TODO: �������� �������� ��������� �����, ������� ����� ���������� ���� ���, ��� ������ ������ ������ ��� ���������� � ����� ���� �������� ����� ���������. �������� �� ���� ����� ����� movementStrategyClass.

// �� ����� ��������� ������ ������������� �� � ���������� ���� ����� ��� � ����� ����, � ����� ������ ��� �������� ���������� ����, �������� ��������� �� �������, �� ����� ����� �� ����� - �� ���������� pointManager./
class Vehicle;
class MovementStrategy;

class Vehicle : public Observer
{
public:
    enum LocationState { AT_POINT, ON_ROAD };
protected:
    MovementStrategy* movementStrategy;
    LocationState currentState;
private:
    int vehicleId;
    std::string vehicleType;
    int currentPointId = 0;
    //int destinationPointId;
    Connection* currentRoad;
    
    int ticksRemaining = 0;
    int currentPathIndex = 0;
    std::vector<Point*> path;
    void moveToNextPointOnPath();
    void onArrivalToPoint();
    int ticksAtCurrentPoint = 0;

public:
    Vehicle();
    Vehicle(int vehicleId, std::string vehicleType);
    ~Vehicle();
    int getVehicleId();
    int getCurrentPointId();
    Connection* getCurrentRoad();
    void setVehicleId(int Id);
    void setVehicleType(std::string vehicleType);
    void setVehiclePoint(int newPointId);
    void setVehicleRoad(Connection* newConnection);
    void setLocationState(LocationState state);
    //void setDestinationPoint(int newDestinationId);
    std::string getVehicleType();
    void setPath(const std::vector<Point*>& newPath);
    void update() override;

    //void moveToRoad(const Connection& road);
    void moveToPoint(int pointId);
    bool canDepartFromPoint();

    std::string currentStatus();

        
};

class Car : public Vehicle
{ // ��������� �� �������� ������ ������� ��� ���������� �� ������������.
private:
    int numberOfDoors;

public:
    Car();
    Car(int vehicleId);
    Car(int vehicleId, std::string vehicleType, int doors);
    int getNumberOfDoors();
    void setNumberOfDoors(int doors);
};

class Truck : public Vehicle
{ // ��������� �� �������� ������ ������� ��� ���������� �� ������������.
private:

public:
    Truck(); // ����������� �� ��������� ��� ��� ���������, ������� ������ ����� ��������
    Truck(int vehicleId);
    Truck(int vehicleId, std::string vehicleType);
};

//class SchoolBus : public Vehicle
//{
//private:
//    std::vector<Point> bus_stations_to_serve;
//    Point school_to_serve;
//
//    Point default_point;
//    std::vector<Point> default_vector;
//
//public:
//    SchoolBus();
//    SchoolBus(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point school_to_serve1, std::vector<Point> bus_stations_to_serve1);
//    Point getSchool();
//    void setSchool(Point school_to_serve1);
//    std::vector<Point> getbus_stations_to_serve();
//    void setbus_stations_to_serve(std::vector<Point> bus_stations_to_serve1);
//};
