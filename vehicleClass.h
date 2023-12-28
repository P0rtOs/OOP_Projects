#pragma once
#include <iostream>
#include "pointManager.h"
#include "tickerClass.h"
#include "movementStrategyClass.h"
#include "connectionClass.h"
#include <vector>

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
{ // Базова одиниця без приоритетів чи особливостей.
public:
    Car();
    Car(int vehicleId);
    Car(int vehicleId, std::string vehicleType);
};

class Truck : public Vehicle
{ // Буде іздити лише між домівками та поштовими офісами.
private:

public:
    Truck();
    Truck(int vehicleId);
    Truck(int vehicleId, std::string vehicleType);
};

class SchoolBus : public Vehicle {
private:
    bool headingToSchool;  // Flag to indicate if the next destination is the school

public:
    SchoolBus(int vehicleId);
};