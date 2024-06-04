
#include "Workspace.h"
#include "PointItem.h"
#include "RoadItem.h"
#include "CarItem.h"
#include "PointPropertiesDialog.h"
#include "PointCreationDialog.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QMenu>
#include <QAction>

#include "CarCreationDialog.h"
#include "CarPropertiesDialog.h"
#include "globalObjects.h"
#include "SimulationController.h"
#include "utility.h"

Workspace::Workspace(QWidget* parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), panning(false), minScaleFactor(0.5), maxScaleFactor(2.0)
{
    setupScene();
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    connect(this, &Workspace::roadViewCreationRequested, this, &Workspace::addRoadView);

    // Load the background image
    backgroundImage = QPixmap("./sprites/background2.jpg");
    isBackgroundLoaded = !backgroundImage.isNull();
}

void Workspace::setupScene()
{
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    // Initialize the scene, set its size, etc.
}

QGraphicsScene* Workspace::getScene() const
{
    return scene;
}

void Workspace::contextMenuEvent(QContextMenuEvent* event)
{
    QGraphicsItem* item = itemAt(event->pos());
    QMenu contextMenu(this);

    if (item && item->type() == PointItemType) {  // PointItem
        PointItem* pointItem = static_cast<PointItem*>(item);

        QAction* createCarAction = contextMenu.addAction("Create Car");
        connect(createCarAction, &QAction::triggered, [this, pointItem]() {
            openCarCreationDialog(pointItem->getId());  // Open car creation dialog
            });

        QAction* showPropertiesAction = contextMenu.addAction("Show Properties");
        connect(showPropertiesAction, &QAction::triggered, [this, pointItem]() {
            showPointProperties(pointItem);
            });

        QAction* initiateConnectionAction = contextMenu.addAction("Make a connection from here");
        connect(initiateConnectionAction, &QAction::triggered, [this, pointItem]() {
            initiateConnection(pointItem);
            });

        if (firstPointForConnection != nullptr && firstPointForConnection != pointItem) {
            QAction* completeConnectionAction = contextMenu.addAction("Make a connection to here");
            connect(completeConnectionAction, &QAction::triggered, [this, pointItem]() {
                completeConnection(pointItem);
                });
        }

        QAction* deletePointAction = contextMenu.addAction("Delete Point");
        connect(deletePointAction, &QAction::triggered, [this, pointItem]() {
            emit pointDeletionRequested(pointItem->getId());
            });
    }
    else if (item && item->type() == CarItemType) {  // CarItem
        CarItem* carItem = static_cast<CarItem*>(item);

        QAction* showCarPropertiesAction = contextMenu.addAction("Show Car Properties");
        connect(showCarPropertiesAction, &QAction::triggered, [this, carItem]() {
            showCarProperties(carItem);
            });

        QAction* deleteCarAction = contextMenu.addAction("Delete Car");
        connect(deleteCarAction, &QAction::triggered, [this, carItem]() {
            emit carDeletionRequested(carItem->getId());
            });
    }
    else {
        QAction* createPointAction = contextMenu.addAction("Create Point");
        connect(createPointAction, &QAction::triggered, [this, event]() {
            openPointCreationDialog(mapToScene(event->pos()));  // Open the dialog
            });
    }

    contextMenu.exec(event->globalPos());
}

void Workspace::openPointCreationDialog(const QPointF& pos)
{
    static int pointId = 0;  // Global point ID counter

    std::vector<Point*> nearestPoints = globalPointManager.getNearestPoints(pos.x(), pos.y(), 5);  // Get 5 nearest points

    PointCreationDialog dialog(pointId, pos.x(), pos.y(), nearestPoints, this);
    if (dialog.exec() == QDialog::Accepted) {
        PointType pointType = dialog.getSelectedPointType();
        std::vector<int> connections = dialog.getSelectedConnections();
        emit pointCreationRequested(pos.x(), pos.y(), pointType, connections);
        pointId++;  // Increment the global point ID counter
    }
}

void Workspace::updateSimulation()
{
    // This function will be called to update the simulation and emit the simulationUpdated signal
    emit simulationUpdated();
}

void Workspace::openCarCreationDialog(int pointId)
{
    static int carId = 0;  // Global car ID counter

    CarCreationDialog dialog(carId, pointId, this);
    if (dialog.exec() == QDialog::Accepted) {
        std::string carType = dialog.getSelectedCarType();
        emit carCreationRequested(pointId, carType);
        carId++;  // Increment the global car ID counter
    }
}


void Workspace::createPointAtPosition(const QPointF& pos)
{
    emit pointCreationRequested(pos.x(), pos.y(), PointType::House, {});
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
    CarItem* car = new CarItem(carId++, x, y, nullptr);
    scene->addItem(car);
}

void Workspace::showPointProperties(PointItem* pointItem)
{
    Point* point = globalPointManager.getPoint(pointItem->getId());
    if (point) {
        PointPropertiesDialog dialog(pointItem, point);

        // Connect the deletion signal from the dialog to the workspace's signal
        connect(&dialog, &PointPropertiesDialog::connectionDeletionRequested, this, &Workspace::connectionDeletionRequested);

        dialog.exec();
    }
}

void Workspace::showCarProperties(CarItem* carItem)
{
    Vehicle* vehicle = globalVehicleManager.getVehicle(carItem->getId());
    if (vehicle) {
        CarPropertiesDialog dialog(carItem, vehicle);
        connect(this, &Workspace::simulationUpdated, &dialog, &CarPropertiesDialog::updateCarProperties);
        dialog.exec();
    }
}


void Workspace::initiateConnection(PointItem* pointItem)
{
    firstPointForConnection = pointItem;
}

void Workspace::completeConnection(PointItem* pointItem)
{
    if (firstPointForConnection) {
        // Calculate distance between points to determine ticks
        double distance = calculateDistance(firstPointForConnection->getX(), firstPointForConnection->getY(), pointItem->getX(), pointItem->getY());
        int ticks = static_cast<int>(distance / 10);  // Convert distance to ticks (you can apply any conversion factor as needed)
        // Add the road visually
        //addRoad(firstPointForConnection, pointItem);

        // Add the connection in the model
        Point* startPoint = globalPointManager.getPoint(firstPointForConnection->getId());
        Point* endPoint = globalPointManager.getPoint(pointItem->getId());

        if (startPoint && endPoint) {
            startPoint->addNeighbor(endPoint->getPointId(), ticks, 100.0);  // Example values for ticks and weight limit
            emit roadViewCreationRequested(firstPointForConnection->getId(), pointItem->getId());
            //endPoint->addNeighbor(startPoint->getPointId(), 10, 100.0);
        }

        firstPointForConnection = nullptr;
    }
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
        viewport()->update();  // Force redraw of the viewport
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

void Workspace::addPoint(int id, double x, double y, PointType pointType)
{
    PointItem* point = new PointItem(id, x, y, pointType);
    scene->addItem(point);
}


void Workspace::addCar(int id, double x, double y, Vehicle* vehicle)
{
    CarItem* car = new CarItem(id, x, y, vehicle);
    scene->addItem(car);
}

void Workspace::addRoadView(int startPointId, int endPointId)
{
    PointItem* startPointItem = nullptr;
    PointItem* endPointItem = nullptr;

    const auto& items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item->type() == PointItemType) {
            PointItem* pointItem = static_cast<PointItem*>(item);
            if (pointItem->getId() == startPointId) {
                startPointItem = pointItem;
            }
            else if (pointItem->getId() == endPointId) {
                endPointItem = pointItem;
            }
        }
        if (startPointItem && endPointItem) {
            break;
        }
    }

    if (startPointItem && endPointItem) {
        RoadItem* road = new RoadItem(startPointItem, endPointItem);
        scene->addItem(road);
    }
}

void Workspace::removeRoadView(int startPointId, int endPointId)
{
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item->type() == RoadItemType) {
            RoadItem* roadItem = static_cast<RoadItem*>(item);
            if ((roadItem->getStartPointId() == startPointId && roadItem->getEndPointId() == endPointId) ||
                (roadItem->getStartPointId() == endPointId && roadItem->getEndPointId() == startPointId)) {
                scene->removeItem(roadItem);
                delete roadItem;
            }
        }
    }
}

void Workspace::removeCarItem(int carId)
{
    const auto& items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item->type() == CarItemType) {
            CarItem* carItem = static_cast<CarItem*>(item);
            if (carItem->getId() == carId) {
                scene->removeItem(carItem);
                delete carItem;
                break;
            }
        }
    }
}


void Workspace::drawBackground(QPainter* painter, const QRectF& rect)
{
    if (isBackgroundLoaded) {
        // Get the visible area in the scene coordinates
        QRectF visibleRect = mapToScene(viewport()->rect()).boundingRect();

        // Calculate the top-left starting position for tiling the background
        qreal left = std::floor(visibleRect.left() / backgroundImage.width()) * backgroundImage.width();
        qreal top = std::floor(visibleRect.top() / backgroundImage.height()) * backgroundImage.height();

        // Draw the tiled background image
        for (qreal x = left; x < visibleRect.right(); x += backgroundImage.width()) {
            for (qreal y = top; y < visibleRect.bottom(); y += backgroundImage.height()) {
                painter->drawPixmap(QPointF(x, y), backgroundImage);
            }
        }
    }

    // Draw other background elements if needed
    QGraphicsView::drawBackground(painter, rect);
}

