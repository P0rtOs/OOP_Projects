
#pragma once

#include "PointItem.h"

class RoadItem : public QGraphicsItem
{
public:
    RoadItem(PointItem* startPoint, PointItem* endPoint);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    int type() const override { return RoadItemType; } // Override the type() method
    void updatePosition(); // Method to update position

private:
    PointItem* startPoint;
    PointItem* endPoint;
};
