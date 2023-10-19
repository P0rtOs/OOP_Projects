#pragma once
#include "pointClass.h"

class Road {
	private:
		int roadId;
		Point roadStartPoint, roadEndPoint;
		int roadSpeedLimit;

	public:
		Road() = default;
		Road( Point& roadStart, Point& roadEnd, int& roadSpeed);
		~Road();
};