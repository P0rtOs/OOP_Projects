#include "connectionClass.h"


//Connection::Connection() : neighborId(-1), ticksToTraverse(-1), weightLimit(-1) {}
Connection::Connection(int neighborId, int ticks, double weightLimit) : neighborId(neighborId), ticksToTraverse(ticks), weightLimit(weightLimit) {}


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


// TODO: ��������� ��� ����� ����������, � ����� ������ ����� ��������� ������ �� ������ - ��� ������� ���������� ������� (�� � ������)