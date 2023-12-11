#include "pointManager.h"

void PointManager::addPoint(Point* point) {
    points.push_back(point);
}

// ������� ���������� ����� ����
void PointManager::removePoint(int pointId) {
    auto it = std::remove_if(points.begin(), points.end(),
        [pointId](Point* p) { return p->getPointId() == pointId; });

    if (it != points.end()) {
        delete* it;  // �������: ��������� ��'���, �� ���� ����� ��������
        points.erase(it, points.end());
    }
}

Point* PointManager::getPoint(int pointId) {
    auto it = std::find_if(points.begin(), points.end(),
        [pointId](Point* p) { return p->getPointId() == pointId; });

    if (it != points.end()) {
        return *it;
    }

    return nullptr;
}
// ���� ��� �� ������� ������������ �����
std::vector<Point*> PointManager::getAllPoints() {
    return points;
}
