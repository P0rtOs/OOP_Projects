#pragma once

#include <QGraphicsItem>

#include "GraphicsItemTypes.h"

class CarItem : public QGraphicsItem
{
public:
    CarItem(int id, double x, double y);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void moveTo(double x, double y);

    int type() const override { return CarItemType; } // Override the type() method

private:
    int id;
    double x, y;
};
