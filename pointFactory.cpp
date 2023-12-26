#include "pointFactory.h"
#include <iostream>

Point* PointFactory::createPoint(int pointId, double x, double y) {
    return new Point(pointId, x, y);
}

Point* PointFactory::createPoint(int pointId, double x, double y, std::vector<Connection*> connection) 
{
    std::cout << "id:" << pointId << x << " " << y;
    /*for (int i = 0; i < connection.size(); i++)
    {
        std::cout << " N id " << connection[i]->getNeighborId << " ticks: " << connection[i]->getTicksToTraverse << " weight: " << connection[i]->getWeightLimit << std::endl;
    }*/
    return new Point(pointId, x, y, connection);
}
//додаткові методи тут
