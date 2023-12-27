#pragma once

class Connection {
private:
	int neighborId;
	int ticksToTraverse;
	double weightLimit;
	
public:
	Connection() = default;
	Connection(int neighborId, int ticks, double weightLimit);
	void setNeighborId(int idToSet);
	void setTicksToTraverse(int TicksToSet);
	void setWeightLimit(double WeightLimitToSet);
	int getNeighborId();
	int getTicksToTraverse();
	double getWeightLimit();
};