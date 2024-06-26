#include "SimulationController.h"
#include "Workspace.h"
#include "Sidebar.h"
#include "CarItem.h"
#include <QTimer>
#include <QCoreApplication>

#include "RoadItem.h"
#include "utility.h"

SimulationController::SimulationController(Workspace* workspace, Sidebar* sidebar, QObject* parent)
    : QObject(parent), workspace(workspace), sidebar(sidebar), timer(new QTimer(this))
{

    connect(sidebar, &Sidebar::startSimulationClicked, this, &SimulationController::startSimulation);
    connect(sidebar, &Sidebar::stopSimulationClicked, this, &SimulationController::stopSimulation);
    connect(sidebar, &Sidebar::simulationSpeedChanged, this, &SimulationController::setSimulationSpeed); // Connect the slider signal

    connect(timer, &QTimer::timeout, this, &SimulationController::updateSimulation);
    timer->start(25); // Update every 0.1 seconds

    connect(workspace, &Workspace::pointPositionChanged, this, &SimulationController::handlePointPositionChanged);
    connect(workspace, &Workspace::pointCreationRequested, this, &SimulationController::handlePointCreationRequest);
    connect(workspace, &Workspace::carCreationRequested, this, &SimulationController::handleCarCreationRequest);  
    connect(workspace, &Workspace::pointDeletionRequested, this, &SimulationController::handlePointDeletionRequest);
    connect(this, &SimulationController::connectionCreatedInView, workspace, &Workspace::addRoadView);
    connect(this, &SimulationController::connectionDeletedInView, workspace, &Workspace::removeRoadView);
    connect(workspace, &Workspace::carDeletionRequested, this, &SimulationController::handleCarDeletionRequest); 
    connect(this, &SimulationController::carDeletionRequested, workspace, &Workspace::removeCarItem);
    connect(this, &SimulationController::simulationUpdated, workspace, &Workspace::updateSimulation);

    connect(workspace, &Workspace::connectionDeletionRequested, this, &SimulationController::handleConnectionDeletion);

    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, &SimulationController::handleApplicationExit);
}

SimulationController::~SimulationController() {}

void SimulationController::startSimulation()
{
    manager.startSimulation();
}

void SimulationController::stopSimulation()
{
    manager.endSimulation();
}


void SimulationController::handlePointCreationRequest(double x, double y, PointType pointType, const std::vector<int>& connections)
{
    static int pointId = 0;  // Global point ID counter
    int newPointId = pointId++;  // Save the new point ID

    auto point = globalPointFactory.createPoint(newPointId, x, y, pointType);
    globalPointManager.addPoint(std::move(point));
    workspace->addPoint(newPointId, x, y, pointType);

    for (int connectionId : connections) {
        Point* connectionPoint = globalPointManager.getPoint(connectionId);
        if (connectionPoint) {
            double distance = calculateDistance(x, y, connectionPoint->getPointX(), connectionPoint->getPointY());
            int ticks = static_cast<int>(distance / 10);
            globalPointManager.getPoint(newPointId)->addNeighbor(connectionId, ticks, 100.0);

            emit connectionCreatedInView(newPointId, connectionId);  // Emit signal for road view creation
        }
    }
}



void SimulationController::handleCarCreationRequest(int pointId, const std::string& carType)
{
    static int carId = 0;  // Global car ID counter
    Vehicle* car = globalVehicleFactory.createVehicle(carId++, carType);
    car->setVehiclePoint(pointId);
    globalVehicleManager.addVehicle(car);

    Point* point = globalPointManager.getPoint(pointId);
    if (point) {
        double x = point->getPointX();
        double y = point->getPointY();
        workspace->addCar(car->getVehicleId(), x, y, car);
    }


    if (manager.isRunning()) {
        manager.getTicker().registerObserver(car);
    }
}


void SimulationController::updateSimulation()
{
    // This method would update the model and emit the signal to update the view
    updateCarItems();  // Update the car items in the view
    emit simulationUpdated();
    //workspace->update();
}

void SimulationController::updateCarItems()
{
    const auto& items = workspace->getScene()->items();
    for (QGraphicsItem* item : items) {
        if (item->type() == CarItemType) {
            CarItem* carItem = static_cast<CarItem*>(item);
            carItem->updatePosition();  // Update each car's position based on the model
        }
    }
}


void SimulationController::handlePointPositionChanged(int id, const QPointF& newPos)
{
    // Update the model with the new position
    // Update the view if necessary
    Point* point = globalPointManager.getPoint(id);
    if (point) {
        point->setPointX(newPos.x());
        point->setPointY(newPos.y());
    }
}

void SimulationController::handlePointDeletionRequest(int pointId)
{
    Point* point = globalPointManager.getPoint(pointId);
    if (point) {
        // Remove cars that are on the way to this point
        auto& vehicles = globalVehicleManager.getVehicles();
        std::vector<Vehicle*> vehiclesToRemove;
        for (Vehicle* vehicle : globalVehicleManager.getVehicles()) {
            if (vehicle->getCurrentPointId() == pointId || (vehicle->getCurrentRoad() && vehicle->getCurrentRoad()->getNeighborId() == pointId)) {
                vehiclesToRemove.push_back(vehicle);
            }
        }

        for (Vehicle* vehicle : vehiclesToRemove) {
            manager.getTicker().unregisterObserver(vehicle);
            emit carDeletionRequested(vehicle->getVehicleId());
            globalVehicleManager.removeVehicle(vehicle);
        }

        // Remove roads connected to this point
        auto neighbors = point->getNeighbors();
        for (Connection* connection : neighbors) {
            int neighborId = connection->getNeighborId();
            Point* neighborPoint = globalPointManager.getPoint(neighborId);
            if (neighborPoint) {
                neighborPoint->removeNeighbor(pointId);
            }
            emit connectionDeletedInView(pointId, neighborId);
        }

        // Remove the point from the model
        globalPointManager.removePoint(pointId);

        // Remove the point and its roads from the view
        const auto& items = workspace->getScene()->items();
        for (QGraphicsItem* item : items) {
            if (item->type() == PointItemType) {
                PointItem* pointItem = static_cast<PointItem*>(item);
                if (pointItem->getId() == pointId) {
                    workspace->getScene()->removeItem(pointItem);
                    delete pointItem;
                    break;
                }
            }
        }

        // Remove associated roads from the view
        QList<QGraphicsItem*> itemsList = workspace->getScene()->items();
        for (QGraphicsItem* item : itemsList) {
            if (item->type() == RoadItemType) {
                RoadItem* roadItem = static_cast<RoadItem*>(item);
                if ((roadItem->getStartPointId() == pointId || roadItem->getEndPointId() == pointId)) {
                    workspace->getScene()->removeItem(roadItem);
                    delete roadItem;
                }
            }
        }
    }
}


void SimulationController::handleCarDeletionRequest(int carId)
{
    Vehicle* car = globalVehicleManager.getVehicle(carId);
    if (car) {
        globalVehicleManager.removeVehicle(car);  // Remove car from model
        const auto& items = workspace->getScene()->items();
        for (QGraphicsItem* item : items) {
            if (item->type() == CarItemType) {
                CarItem* carItem = static_cast<CarItem*>(item);
                if (carItem->getId() == carId) {
                    workspace->getScene()->removeItem(carItem);  // Remove car from view
                    delete carItem;
                    break;
                }
            }
        }
    }
}


void SimulationController::handleConnectionDeletion(int startPointId, int endPointId)
{
    Point* startPoint = globalPointManager.getPoint(startPointId);
    Point* endPoint = globalPointManager.getPoint(endPointId);

    if (startPoint && endPoint) {
        startPoint->removeNeighbor(endPointId);
        endPoint->removeNeighbor(startPointId);
        // Emit a signal to remove the road view if needed
        emit connectionDeletedInView(startPointId, endPointId);
    }
}

void SimulationController::handleApplicationExit()
{
    stopSimulation();  // Ensure the simulation thread is stopped before the application exits
}

void SimulationController::setWorkspace(Workspace* workspace)
{
    this->workspace = workspace;
}

void SimulationController::setSimulationSpeed(int speed)
{

    int ticksPerSecond;
    switch (speed) {
    case 1: ticksPerSecond = 10; break;  // Slower
    case 2: ticksPerSecond = 20; break;  // Slow
    case 3: ticksPerSecond = 40; break;  // Normal
    case 4: ticksPerSecond = 60; break;  // Fast
    case 5: ticksPerSecond = 80; break;  // Faster
    default: ticksPerSecond = 40; break; // Default to Normal
    }

    int interval = 1000 / ticksPerSecond;
    timer->setInterval(interval/2);
    manager.setSimulationSpeed(ticksPerSecond);
}