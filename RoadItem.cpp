#include "RoadItem.h"
#include <QPainter>

RoadItem::RoadItem(PointItem* startPoint, PointItem* endPoint)
    : startPoint(startPoint), endPoint(endPoint)
{
    setZValue(-1);  // Ensure roads are drawn below points
}

QRectF RoadItem::boundingRect() const
{
    return QRectF(startPoint->pos(), endPoint->pos()).normalized();
}

void RoadItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    painter->drawLine(startPoint->pos(), endPoint->pos());
}



void RoadItem::updatePosition()
{
    prepareGeometryChange();
    update();
}
