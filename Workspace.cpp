
#include "Workspace.h"
#include "PointItem.h"
#include "RoadItem.h"
#include "CarItem.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QMenu>
#include <QAction>

Workspace::Workspace(QWidget* parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), panning(false), minScaleFactor(0.5), maxScaleFactor(2.0)
{
    setupScene();
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void Workspace::setupScene()
{
    scene->setSceneRect(-500, -500, 1000, 1000);
    // Initialize the scene, set its size, etc.
}

void Workspace::contextMenuEvent(QContextMenuEvent* event)
{
    QGraphicsItem* item = itemAt(event->pos());
    QMenu contextMenu(this);

    if (item && item->type() == PointItemType) {  // PointItem
        QAction* createCarAction = contextMenu.addAction("Create Car");
        connect(createCarAction, &QAction::triggered, [this, item]() {
            PointItem* point = static_cast<PointItem*>(item);
            createCarAtPoint(point);
            });
    }
    else {
        QAction* createPointAction = contextMenu.addAction("Create Point");
        connect(createPointAction, &QAction::triggered, [this, event]() {
            createPointAtPosition(mapToScene(event->pos()));
            });
    }

    contextMenu.exec(event->globalPos());
}



//void Workspace::contextMenuEvent(QContextMenuEvent* event)
//{
//    QMenu contextMenu(this);
//    QAction* createPointAction = contextMenu.addAction("Create Point");
//    QAction* createVehicleAction = contextMenu.addAction("Create Vehicle");
//
//    connect(createPointAction, &QAction::triggered, [this, event]() {
//        createPointAtPosition(mapToScene(event->pos()));
//        });
//
//    connect(createVehicleAction, &QAction::triggered, [this, event]() {
//        createVehicleAtPosition(mapToScene(event->pos()));
//        });
//
//    contextMenu.exec(event->globalPos());
//
//    /*QAction* selectedAction = contextMenu.exec(event->globalPos());
//    if (selectedAction == createPointAction) {
//         Handle creating a point
//    }
//    else if (selectedAction == createVehicleAction) {
//         Handle creating a vehicle
//    }*/
//}

void Workspace::createPointAtPosition(const QPointF& pos)
{
    emit pointCreationRequested(pos.x(), pos.y());
}

void Workspace::updatePointPosition(int id, const QPointF& newPos)
{
    emit pointPositionChanged(id, newPos);
}


void Workspace::createCarAtPoint(PointItem* point)
{
    static int carId = 0;  // Static ID for simplicity
    double x = point->getX();
    double y = point->getY();
    CarItem* car = new CarItem(carId++, x, y);
    scene->addItem(car);
}

void Workspace::wheelEvent(QWheelEvent* event)
{
    const double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        if (transform().m11() < maxScaleFactor)
            scale(scaleFactor, scaleFactor);
    }
    else {
        if (transform().m11() > minScaleFactor)
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}


void Workspace::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        lastMousePos = event->pos();
        panning = true;
        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void Workspace::mouseMoveEvent(QMouseEvent* event)
{
    if (panning) {
        QPoint delta = event->pos() - lastMousePos;
        lastMousePos = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Workspace::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        panning = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void Workspace::addPoint(int id, double x, double y)
{
    PointItem* point = new PointItem(id, x, y);
    scene->addItem(point);
}

void Workspace::addRoad(PointItem* startPoint, PointItem* endPoint)
{
    RoadItem* road = new RoadItem(startPoint, endPoint);
    scene->addItem(road);
}

void Workspace::addCar(int id, double x, double y)
{
    CarItem* car = new CarItem(id, x, y);
    scene->addItem(car);
}