#include "connectionClass.h"

#include <iostream>

Connection::Connection(int neighborId, int ticks, double weightLimit) : neighborId(neighborId), ticksToTraverse(ticks), weightLimit(weightLimit) {
	std::cout << "Connection to " << getNeighborId() << " created (ticksToTraverse: " << getTicksToTraverse() << ", weightLimit: " << getWeightLimit() << ").\n";
}

void Connection::setNeighborId(int idToSet)
{
	this->neighborId = idToSet;
}

void Connection::setTicksToTraverse(int TicksToSet)
{
	this->ticksToTraverse = TicksToSet;
}

void Connection::setWeightLimit(double WeightLimitToSet)
{
	this->weightLimit = WeightLimitToSet;
}

int Connection::getNeighborId() { return neighborId; }
int Connection::getTicksToTraverse() { return ticksToTraverse; }
double Connection::getWeightLimit() { return weightLimit; }

