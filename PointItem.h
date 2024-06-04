#pragma once

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>

#include "GraphicsItemTypes.h"
#include "pointType.h"

class PointItem : public QGraphicsObject
{
    Q_OBJECT

public:
    PointItem(int id, double x, double y, PointType pointType, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    int getId() const;
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
    PointType pointType;
    QPixmap pointSprite;
    QColor shadowColor;

    void loadSprite();
    void drawShadow(QPainter* painter);  // New method to draw shadow
};
