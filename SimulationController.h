#pragma once

#include <QObject>
#include "Manager.h"

class Workspace;
class Sidebar;

class SimulationController : public QObject
{
    Q_OBJECT

public:
    explicit SimulationController(Workspace* workspace, Sidebar* sidebar, QObject* parent = nullptr);
    ~SimulationController();

public slots:
    void startSimulation();
    void stopSimulation();
    void createPoint();
    void handlePointCreationRequest(double x, double y);
    void createVehicle();
    void createConnection();
    void handlePointPositionChanged(int id, const QPointF& newPos);
    void handleApplicationExit();

signals:
    void simulationUpdated();

private:
    Manager manager;
    Workspace* workspace;
    Sidebar* sidebar;

    void updateSimulation();
};
