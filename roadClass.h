#pragma once
#include "pointClass.h"

class Road {
	private:
		int roadId;
		Point roadStartPoint, roadEndPoint;
		double roadSpeedLimit;
	public: 
		Road(Point roadStart, Point roadEnd, double roadSpeed);
		~Road();
};