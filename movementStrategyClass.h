#pragma once
#include "vehicleClass.h"

class Vehicle;

class MovementStrategy {
public:
	MovementStrategy();
	//virtual void move(Vehicle& vehicle) = 0;
	vector<Point*> dijkstraShortestPath(int sourceId, int targetId, Vehicle& vehicle);
	virtual Point* returnRandomDestination(int currentPointId) = 0;
	virtual std::string returnStrategyType() = 0;
	virtual Point* returnStartingPoint() = 0;
};

class StandartCarMovingStrategy : public MovementStrategy {
public:
	StandartCarMovingStrategy();
	std::string returnStrategyType() override;
	//void move(Vehicle& vehicle) override;
	Point* returnRandomDestination(int currentPointId) override;
	Point* returnStartingPoint() override;
};

class TruckMovingStrategy : public MovementStrategy {
public:
	TruckMovingStrategy();
	std::string returnStrategyType() override;
	Point* returnRandomDestination(int currentPointId) override;
	Point* returnStartingPoint() override;
	Point* findRandomPointOfType(PointType type);
};

class SchoolBusMovingStrategy : public MovementStrategy {
private:
	Point* school; // The school the bus serves
	bool headingToSchool; // Flag to indicate if the next destination is the school

public:
	SchoolBusMovingStrategy();
	std::string returnStrategyType() override;
	Point* returnRandomDestination(int currentPointId) override;
	Point* findRandomPointOfType(PointType type);
	Point* returnStartingPoint() override;

private:
	Point* returnRandomHouse();
	Point* findRandomSchool();
};



// TODO: �������� ��������� ��� ����� ������������ ������ ���� ����� ( �����������, ��������, �� )  