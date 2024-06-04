#pragma once

#include "PointItem.h"
#include <QGraphicsItem>

class RoadItem : public QGraphicsItem
{
public:
    RoadItem(PointItem* startPoint, PointItem* endPoint);

    int getStartPointId() const;
    int getEndPointId() const;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    int type() const override { return RoadItemType; }
    void updatePosition();

private:
    PointItem* startPoint;
    PointItem* endPoint;
};
