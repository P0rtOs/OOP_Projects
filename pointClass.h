#pragma once
#include <vector>
#include "connectionClass.h"

using std::vector;

class Point {
	private:
		int pointId;
		double pointX, pointY;
		std::vector<Connection*> neighbors;

	public:
		Point();
		Point(int pointId, double pointX, double pointY);
		Point(int pointId, double pointX, double pointY, std::vector<Connection*> connections);
		~Point();
		const int getPointId();
		double getPointX();
		double getPointY();
		void setPointId(int Id);
		void setPointX(double x);
		void setPointY(double y);
		void setNeighbor(std::vector<Connection*> connectionsToSet);
		void addNeighbor(int neighborId, int ticks, double weightLimit);
		const vector<Connection*> getNeighbor() const;

};