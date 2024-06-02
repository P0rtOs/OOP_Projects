#pragma once

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QObject>

#include "GraphicsItemTypes.h"

class RoadItem;

class PointItem : public QGraphicsObject
{
    Q_OBJECT

public:
    PointItem(int id, double x, double y);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    int getId() const;
    void setId(int newId);  // Method to set the ID
    double getX() const;
    double getY() const;

    int type() const override { return PointItemType; } // Override the type() method

signals:
    void positionChanged(int id, const QPointF& newPos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    int id;
    double x, y;
};
