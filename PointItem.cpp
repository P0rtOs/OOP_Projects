#include "PointItem.h"
#include "pointClass.h"
#include <QPainter>

PointItem::PointItem(int id, double x, double y, PointType pointType, QGraphicsItem* parent)
    : QGraphicsObject(parent), id(id), x(x), y(y), pointType(pointType), shadowColor(Qt::darkGray)
{
    setPos(x, y);
    loadSprite();
}

int PointItem::getId() const
{
    return id;
}

double PointItem::getX() const
{
    return x;
}

double PointItem::getY() const
{
    return y;
}

QRectF PointItem::boundingRect() const
{
    return QRectF(-pointSprite.width() / 2, -pointSprite.height() / 2, pointSprite.width(), pointSprite.height());
}


void PointItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Draw the shadow
    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->drawEllipse(-pointSprite.width() / 2 * 1.8, pointSprite.height() / 2 - 30, pointSprite.width()*1.8, pointSprite.height() / 2);

    // Draw the sprite
    painter->drawPixmap(-pointSprite.width() / 2, -pointSprite.height() / 2, pointSprite);
}

//void PointItem::drawShadow(QPainter* painter)
//{
//    // Define the shadow properties
//    QPointF shadowOffset(0, 10);  // Offset of the shadow to the bottom
//    QSize shadowSize(pointSprite.width() * 0.6, pointSprite.height() * 0.3);  // Shadow size (adjust as needed)
//
//    painter->setBrush(QBrush(shadowColor));
//    painter->setPen(Qt::NoPen);
//    painter->drawEllipse(QPointF(-shadowSize.width() / 2, -shadowSize.height() / 2) + shadowOffset, shadowSize.width() / 2, shadowSize.height() / 2);
//}

void PointItem::loadSprite()
{
    QPixmap originalPixmap;
    if (pointType == PointType::PostOffice || pointType == PointType::School) {
        originalPixmap = QPixmap("./sprites/city1.png");
    }
    else if (pointType == PointType::House || pointType == PointType::Hospital) {
        originalPixmap = QPixmap("./sprites/city2.png");
    }
    else if (pointType == PointType::PoliceStation) {
        originalPixmap = QPixmap("./sprites/city3.png");
    }
    else {
        originalPixmap = QPixmap("./sprites/city1.png");  // Default sprite
    }

    if (!originalPixmap.isNull()) {
        pointSprite = originalPixmap.scaled(originalPixmap.width(), originalPixmap.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    setTransformOriginPoint(boundingRect().center());
}

QVariant PointItem::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemPositionChange) {
        emit positionChanged(id, value.toPointF());
    }
    return QGraphicsItem::itemChange(change, value);
}

void PointItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
    // Custom behavior on mouse press, if needed
}
