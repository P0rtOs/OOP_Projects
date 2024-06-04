#include "CarItem.h"
#include "vehicleClass.h"
#include <QPainter>
#include "globalObjects.h"

CarItem::CarItem(int id, double x, double y, Vehicle* vehicle, QGraphicsItem* parent)
    : QGraphicsItem(parent), id(id), vehicle(vehicle)
{
    setPos(x, y);
    setZValue(1);  // Ensure cars are drawn above roads
    loadSprite();
}

int CarItem::getId() const
{
    return id;
}

QRectF CarItem::boundingRect() const
{
    return QRectF(-carSprite.width() / 2, -carSprite.height() / 2, carSprite.width(), carSprite.height());
}

void CarItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(-carSprite.width() / 2, -carSprite.height() / 2, carSprite);
}

void CarItem::updatePosition()
{
    if (vehicle->getLocationState() == Vehicle::AT_POINT) {
        Point* point = globalPointManager.getPoint(vehicle->getCurrentPointId());
        if (point) {
            setPos(point->getPointX(), point->getPointY());
            setRotation(0);  // Reset rotation when at a point
        }
    }
    else if (vehicle->getLocationState() == Vehicle::ON_ROAD) {
        Point* currentPoint = globalPointManager.getPoint(vehicle->getCurrentPointId());
        Point* nextPoint = globalPointManager.getPoint(vehicle->getCurrentRoad()->getNeighborId());
        if (currentPoint && nextPoint) {
            double ratio = 1.0 - static_cast<double>(vehicle->getTicksRemaining()) / vehicle->getCurrentRoad()->getTicksToTraverse();
            double newX = currentPoint->getPointX() + ratio * (nextPoint->getPointX() - currentPoint->getPointX());
            double newY =  60 + currentPoint->getPointY() + ratio * (nextPoint->getPointY() - currentPoint->getPointY());

            // Calculate the angle of rotation
            double dx = nextPoint->getPointX() - currentPoint->getPointX();
            double dy = nextPoint->getPointY() - currentPoint->getPointY();
            double angle = qRadiansToDegrees(qAtan2(dy, dx));
            setRotation(angle + 90);  // Add 90 degrees to align the sprite's front with the direction of movement

            // Apply offset to the right
            double offset = 15.0;
            double offsetX = -offset * qSin(qDegreesToRadians(angle));
            double offsetY = offset * qCos(qDegreesToRadians(angle));
            setPos(newX + offsetX, newY + offsetY);
        }
    }
}

void CarItem::loadSprite()
{
    if (vehicle->getVehicleType() == "Car") {
        carSprite = QPixmap("./sprites/car_sprite.png");

    }
    else if (vehicle->getVehicleType() == "Truck") {
        carSprite = QPixmap("./sprites/van_sprite.png");
    }
    else if (vehicle->getVehicleType() == "SchoolBus") {
        carSprite = QPixmap("./sprites/school_sprite.png");
    }
    else {
        carSprite = QPixmap("./sprites/car_sprite.png");
    }

    if (!carSprite.isNull()) {
        carSprite = carSprite.scaled(carSprite.width() / 2, carSprite.height() / 2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    setTransformOriginPoint(boundingRect().center());
}
