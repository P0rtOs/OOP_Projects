#include "SimulationController.h"
#include "Workspace.h"
#include "Sidebar.h"
#include <QTimer>
#include <QCoreApplication>

SimulationController::SimulationController(Workspace* workspace, Sidebar* sidebar, QObject* parent)
    : QObject(parent), workspace(workspace), sidebar(sidebar)
{
    connect(sidebar, &Sidebar::createPointClicked, this, &SimulationController::createPoint);
    connect(sidebar, &Sidebar::createVehicleClicked, this, &SimulationController::createVehicle);
    connect(sidebar, &Sidebar::createConnectionClicked, this, &SimulationController::createConnection);
    connect(sidebar, &Sidebar::startSimulationClicked, this, &SimulationController::startSimulation);
    connect(sidebar, &Sidebar::stopSimulationClicked, this, &SimulationController::stopSimulation);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulationController::updateSimulation);
    timer->start(1500); // Update every 1.5 seconds

    connect(workspace, &Workspace::pointPositionChanged, this, &SimulationController::handlePointPositionChanged);
    connect(workspace, &Workspace::pointCreationRequested, this, &SimulationController::handlePointCreationRequest);

    // Connect the application exit signal to the handleApplicationExit slot
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

void SimulationController::createPoint()
{
    QPointF scenePos = workspace->mapToScene(workspace->viewport()->rect().center());
    emit workspace->pointCreationRequested(scenePos.x(), scenePos.y());
}

void SimulationController::handlePointCreationRequest(double x, double y)
{
    static int pointId = 0;  // Global point ID counter
    auto point = globalPointFactory.createPoint(pointId++, x, y);
    globalPointManager.addPoint(std::move(point));
    workspace->addPoint(pointId - 1, x, y);
}

void SimulationController::createVehicle()
{
    // Logic to create a vehicle in the model and update the view
    /*QPointF scenePos = workspace->mapToScene(workspace->viewport()->rect().center());
    workspace->createVehicleAtPosition(scenePos);*/
}

void SimulationController::createConnection()
{
    // Logic to create a connection in the model and update the view
}

void SimulationController::updateSimulation()
{
    // This method would update the model and emit the signal to update the view
    emit simulationUpdated();
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

void SimulationController::handleApplicationExit()
{
    stopSimulation();  // Ensure the simulation thread is stopped before the application exits
}
