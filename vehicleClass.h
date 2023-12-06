#pragma once
#include <iostream>
#include "pointClass.h"
#include "tickerClass.h"
#include "movementStrategyClass.h"
#include "connectionClass.h"
#include <vector>

// TODO: Подумать, сколько должна каждая машина проезжать за тик. 
// TODO: Зачем нам количество дверей? Если нету причини и это просто bloat - удалить.

// TODO: Переписать логику нахождение цели машини - это должен делать movementStrategyClass, а сюда должен лишь передавать, машина должна сама.
// TODO: Возможно написать отдельный класс, который будет заниматься лишь тем, что каждую машину каждый тик приближать к своей цели согласно своей стратегии. Возможно он даже будет самим movementStrategyClass.
class Vehicle : public Observer
{
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
        Vehicle(int vehicleId, int currentPointId, int goalPointId, std::string vehicleType);
        ~Vehicle();
        int getVehicleId();
        void setVehicleId(int Id);
        void setVehicleType(std::string vehicleType);
        void setVehiclePoint(int newPointId);
        void setVehicleRoad(const Connection& newConnection);
        void setVehicleGoalPoint(int newGoalPointId);
        std::string getVehicleType();
        void update() override;

        void moveToRoad(const Connection& road);
        void moveToPoint(int pointId);

        std::string getLocationInfo();
        
};

class Car : public Vehicle
{ // планується як звичайна базова одиниця без приоритетів чи особливостей.
    private:
        int numberOfDoors;

    public:
        Car();
        Car(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, int doors);
        int getNumberOfDoors();
        void setNumberOfDoors(int doors);
};

class Truck : public Vehicle
{ // планується як звичайна базова одиниця без приоритетів чи особливостей.
    private:
        Point aim;
        Point default_point;

    public:
        Truck(); // конструткор по стандарту для цілі вантажівки, можливо якийсь центр логістики
        Truck(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point point);
        Point getAim();
        void setAim(Point point);
};

class SchoolBus : public Vehicle
{
    private:
        std::vector<Point> bus_stations_to_serve;
        Point school_to_serve;

        Point default_point;
        std::vector<Point> default_vector;

    public:
        SchoolBus();
        SchoolBus(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point school_to_serve1, std::vector<Point> bus_stations_to_serve1);
        Point getSchool();
        void setSchool(Point school_to_serve1);
        std::vector<Point> getbus_stations_to_serve();
        void setbus_stations_to_serve(std::vector<Point> bus_stations_to_serve1);
};
