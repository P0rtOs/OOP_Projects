#pragma once
#include "pointClass.h"

class PointFactory {
public:
    // ����� ��� ��������� ������������ Point
    Point* createPoint(int pointId, double x, double y);
    Point* createPoint(int pointId, double x, double y, std::vector<Connection*>& connection, int neightbourAmount);

    // ��� ����� ������ �������� ������ ��� ��������� ����� ���� Point
};
