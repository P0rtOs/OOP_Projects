#pragma once

#include <QGraphicsItem>
#include <QPixmap>

#include "GraphicsItemTypes.h"

class Vehicle;

class CarItem : public QGraphicsItem
{
public:
    CarItem(int id, double x, double y, Vehicle* vehicle, QGraphicsItem* parent = nullptr);

    int getId() const;
    void updatePosition();
    QRectF boundingRect() const override;  // Override the boundingRect method
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    int type() const override { return CarItemType; }

private:
    int id;
    Vehicle* vehicle;
    QPixmap carSprite;  // Sprite for the car

    void loadSprite();  // New method to load the appropriate sprite
};
