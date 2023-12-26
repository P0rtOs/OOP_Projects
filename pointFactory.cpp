#include "pointFactory.h"

Point* PointFactory::createPoint(int pointId, double x, double y) {
    return new Point(pointId, x, y);
}

Point* PointFactory::createPoint(int pointId, double x, double y, std::vector<Connection*> connection) 
{
    return new Point(pointId, x, y, connection);
}
//додаткові методи тут
