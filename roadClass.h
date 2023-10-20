#pragma once
#include "pointClass.h"

class Road {
	private:
		int roadId;
		Point* roadStartPoint;
		Point* roadEndPoint;
		int roadSpeedLimit;

	public:
		Road();
		Road(Point& roadStartPoint, Point& roadEndPoint, int roadSpeed);
		~Road();
		int getRoadId(void);
		Point* getRoadStartPoint();
		Point* getRoadEndPoint();
		int* getSpeedLimit();
};