#include "connectionClass.h"


Connection::Connection() : neighborId(-1), ticksToTraverse(-1), weightLimit(-1) {}
Connection::Connection(int neighbourId, int ticks, double weightLimit) : neighborId(neighborId), ticksToTraverse(ticks), weightLimit(weightLimit) {}

int Connection::getNeighborId() { return neighborId; }
int Connection::getTicksToTraverse() { return ticksToTraverse; }
double Connection::getWeightLimit() { return weightLimit; }


// TODO: ѕродумать как будет сохран€тс€, в каком именно месте находитс€ машина на дороге - дл€ будущей реализации графики (ну и просто)