#pragma once
#include "connectionClass.h"
#include "pointType.h"

#include <vector>
#include <memory>


using std::vector;



class Point {
private:
	int pointId;
	double pointX, pointY;
	PointType pointType;

	std::vector<std::unique_ptr<Connection>> neighbors;

public:
	Point();
	Point(int pointId, double pointX, double pointY);
	Point(int pointId, double pointX, double pointY, PointType pointType);
	Point(int pointId, double pointX, double pointY, std::vector<Connection*> connections);
	Point(int pointId, double pointX, double pointY, PointType pointType, std::vector<Connection*> connections);
	const int getPointId();
	double getPointX();
	double getPointY();
	PointType getPointType();
	void setPointId(int Id);
	void setPointX(double x);
	void setPointY(double y);
	void setPointType(PointType pointType);
	void setNeighbor(std::vector<Connection*> connectionsToSet);
	void addConnection(int pointId, int ticks, double weightLimit);
	void addConnection(std::unique_ptr<Connection> connection);
	void addNeighbor(int neighborId, int ticks, double weightLimit);
	void removeNeighbor(int neighborId);
	bool hasConnection(int pointId) const;
	vector<Connection*> getNeighbors();

};