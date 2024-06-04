#include "RoadItem.h"
#include <QPainter>

RoadItem::RoadItem(PointItem* startPoint, PointItem* endPoint)
    : startPoint(startPoint), endPoint(endPoint)
{
    setZValue(-2);  // Ensure roads are drawn below points
}

QRectF RoadItem::boundingRect() const
{
    return QRectF(startPoint->pos(), endPoint->pos()).normalized();
}

void RoadItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPointF startPointOffset = startPoint->pos() + QPointF(0, startPoint->boundingRect().height() / 2);
    QPointF endPointOffset = endPoint->pos() + QPointF(0, endPoint->boundingRect().height() / 2);

    QPen pen(Qt::black, 10); // Border lines
    pen.setWidth(60);  // Total width of the road
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::darkGray)); // Asphalt color
    painter->drawLine(startPointOffset, endPointOffset);

    QPen middleLinePen(Qt::white, 3, Qt::DashLine);  // Middle dashed line
    middleLinePen.setWidth(2);
    painter->setPen(middleLinePen);
    painter->drawLine(startPointOffset, endPointOffset);

    QPen borderLinePen(Qt::white, 5); // Border lines
    painter->setPen(borderLinePen);

    QLineF line(startPointOffset, endPointOffset);
    QLineF normal = line.normalVector().unitVector();
    normal.setLength(30);  // Half the width of the road

}

void RoadItem::updatePosition()
{
    prepareGeometryChange();
    update();
}

int RoadItem::getStartPointId() const
{
    return startPoint->getId();
}

int RoadItem::getEndPointId() const
{
    return endPoint->getId();
}


