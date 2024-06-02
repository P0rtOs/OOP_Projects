#include "PointItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

PointItem::PointItem(int id, double x, double y)
    : id(id), x(x), y(y)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setPos(x, y);
}

QRectF PointItem::boundingRect() const
{
    return QRectF(-15, -15, 30, 30);
}

void PointItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(isSelected() ? Qt::red : Qt::blue);
    painter->drawEllipse(-10, -10, 20, 20);

    painter->setPen(Qt::white);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(id));
}

int PointItem::getId() const
{
    return id;
}

void PointItem::setId(int newId)
{
    id = newId;
    update();  // Redraw the item with the new ID
}

double PointItem::getX() const
{
    return x;
}

double PointItem::getY() const
{
    return y;
}



QVariant PointItem::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionChange) {
        emit positionChanged(id, value.toPointF());
    }
    return QGraphicsObject::itemChange(change, value); // Use QGraphicsObject instead of QGraphicsItem
}

void PointItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
    // Custom behavior on mouse press, if needed
}
