#pragma once

class Connection {
private:
	int neighborId;
	int ticksToTraverse;
	double weightLimit;
	
public:
	Connection() = default;
	Connection(int neighborId, int ticks, double weightLimit);
	int getNeighborId();
	int getTicksToTraverse();
	double getWeightLimit();
};