#pragma once
#include <iostream>
#include "roadClass.h"
#include <vector>

class Vehicle {
	private:
		int vehicleId;
		Road* vehicleRoad;
		std::string vehicleType;
        int currentPointId;

	public:
		Vehicle();
		Vehicle(int vehicleId, Road& vehicleRoad, std::string vehicleType);
		~Vehicle();
		int getVehicleId();
		Road* getVehicleRoad();
		void setVehicleId(int Id);
		void setVehicleRoad(Road& thisRoad);
		void setVehicleType(std::string vehicleType);
        void setVehiclePoint(int newPointId);
		std::string getVehicleType();

};

class Car : public Vehicle {  //плануЇтьс€ €к звичайна базова одиниц€ без приоритет≥в чи особливостей.
private:
    int numberOfDoors;

public:
    Car();
    Car(int vehicleId, Road& vehicleRoad, std::string vehicleType, int doors);
    int getNumberOfDoors();
    void setNumberOfDoors(int doors);
};

class Truck : public Vehicle {  //плануЇтьс€ €к звичайна базова одиниц€ без приоритет≥в чи особливостей.
private:
    Point aim;

    Point default_point;

public:
    Truck();    //конструткор по стандарту дл€ ц≥л≥ вантаж≥вки, можливо €кийсь центр лог≥стики
    Truck(int vehicleId, Road& vehicleRoad, std::string vehicleType, Point point);
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
    School_bus(int vehicleId, Road& vehicleRoad, std::string vehicleType, Point school_to_serve1, std::vector<Point> bus_stations_to_serve1);
    Point getSchool();
    void setSchool(Point school_to_serve1);
    std::vector<Point> getbus_stations_to_serve();
    void setbus_stations_to_serve(std::vector<Point> bus_stations_to_serve1);
};


