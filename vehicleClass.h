#pragma once
#include <iostream>
#include "pointClass.h"
#include <vector>

class Vehicle {
	private:
		int vehicleId;
		std::string vehicleType;
        int currentPointId;
        int goalPointId;

	public:
		Vehicle();
		Vehicle(int vehicleId, int currentPointId, int goalPointId, std::string vehicleType);
		~Vehicle();
		int getVehicleId();
		void setVehicleId(int Id);
		void setVehicleType(std::string vehicleType);
        void setVehiclePoint(int newPointId);
        void setVehicleGoalPoint(int newGoalPointId);
		std::string getVehicleType();

};

class Car : public Vehicle {  //плануЇтьс€ €к звичайна базова одиниц€ без приоритет≥в чи особливостей.
private:
    int numberOfDoors;

public:
    Car();
    Car(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, int doors);
    int getNumberOfDoors();
    void setNumberOfDoors(int doors);
};

class Truck : public Vehicle {  //плануЇтьс€ €к звичайна базова одиниц€ без приоритет≥в чи особливостей.
private:
    Point aim;

    Point default_point;

public:
    Truck();    //конструткор по стандарту дл€ ц≥л≥ вантаж≥вки, можливо €кийсь центр лог≥стики
    Truck(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point point);
    Point getAim();
    void setAim(Point point);
};

class School_bus : public Vehicle {  
private:
    std::vector<Point> bus_stations_to_serve;
    Point school_to_serve;

    Point default_point;
    std::vector<Point> default_vector;

public:
    School_bus();
    School_bus(int vehicleId, int newVehicleCurrentPointId, int newVehicleGoalPoint, std::string vehicleType, Point school_to_serve1, std::vector<Point> bus_stations_to_serve1);
    Point getSchool();
    void setSchool(Point school_to_serve1);
    std::vector<Point> getbus_stations_to_serve();
    void setbus_stations_to_serve(std::vector<Point> bus_stations_to_serve1);
};


