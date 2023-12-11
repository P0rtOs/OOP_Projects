#include "pointFactory.h"

Point* PointFactory::createPoint(int pointId, double x, double y) {
    return new Point(pointId, x, y);
}

//додаткові методи тут
