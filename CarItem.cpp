#include "CarItem.h"
#include <QPainter>

CarItem::CarItem(int id, double x, double y)
    : id(id), x(x), y(y)
{
    setPos(x, y);
}

QRectF CarItem::boundingRect() const
{
    return QRectF(-10, -5, 20, 10);
}

void CarItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(Qt::green);
    painter->drawRect(-10, -5, 20, 10);
}

void CarItem::moveTo(double x, double y)
{
    setPos(x, y);
}
