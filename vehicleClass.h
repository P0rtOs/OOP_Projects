#pragma once
#include <iostream>
#include "pointClass.h"
#include "pointManager.h"
#include "tickerClass.h"
#include "movementStrategyClass.h"
#include "connectionClass.h"
#include <vector>

// TODO: ѕодумать, сколько должна кажда€ машина проезжать за тик. 
// TODO: «ачем нам количество дверей? ≈сли нету причини и это просто bloat - удалить.

// TODO: ѕереписать логику нахождение цели машини - это должен делать movementStrategyClass, а сюда должен лишь передавать, машина должна сама.
// TODO: ¬озможно написать отдельный класс, который будет заниматьс€ лишь тем, что каждую машину каждый тик приближать к своей цели согласно своей стратегии. ¬озможно он даже будет самим movementStrategyClass.

// ћы можем создавать машину исключительно из еЄ параметров типо какой тип и какой айди, а потом только при проверке следующего тика, рандомно назначать ей позицию, но тогда нужно ей сразу - же передавать pointManager./
class Vehicle : public Observer
{
protected:
    MovementStrategy* movementStrategy;

public:
    enum LocationState { AT_POINT, ON_ROAD };

private:
    int vehicleId;
    std::string vehicleType;
    int currentPointId;
    int goalPointId;
    Connection currentRoad;
    LocationState currentState;

public:
    Vehicle();
    Vehicle(int vehicleId, std::string vehicleType);
    ~Vehicle();
    int getVehicleId();
    void setVehicleId(int Id);
    void setVehicleType(std::string vehicleType);
    void setVehiclePoint(int newPointId);
    void setVehicleRoad(const Connection& newConnection);
    void setVehicleGoalPoint(int newGoalPointId);
    void setMovementStrategyPM(PointManager* pm);
    std::string getVehicleType();
    void update() override;

    void moveToRoad(const Connection& road);
    void moveToPoint(int pointId);

    std::string getLocationInfo();
        
};

class Car : public Vehicle
{ // плануЇтьс€ €к звичайна базова одиниц€ без приоритет≥в чи особливостей.
private:
    int numberOfDoors;

public:
    Car();
    Car(int vehicleId, std::string vehicleType, int doors, PointManager* pm);
    int getNumberOfDoors();
    void setNumberOfDoors(int doors);
};

class Truck : public Vehicle
{ // плануЇтьс€ €к звичайна базова одиниц€ без приоритет≥в чи особливостей.
private:
    Point aim;
    Point default_point;

public:
    Truck(); // конструткор по стандарту дл€ ц≥л≥ вантаж≥вки, можливо €кийсь центр лог≥стики
    Truck(int vehicleId, std::string vehicleType, PointManager* pm);
    Point getAim();
    void setAim(Point point);
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
