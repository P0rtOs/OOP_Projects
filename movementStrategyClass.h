#pragma once
#include "vehicleClass.h"

class MovementStrategy {
public:
	virtual void move(Vehicle& vehicle) = 0;
};

class StandartCarMovingStrategy : public MovementStrategy {
public:
	void move(Vehicle& vehicle) override;
};


// TODO: �������� ��������� ��� ����� ������������ ������ ���� ����� ( �����������, ��������, �� )  