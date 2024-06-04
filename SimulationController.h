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
	void setWorkspace(Workspace* workspace);
	~SimulationController();

public slots:
	void startSimulation();
	void stopSimulation();
	void handlePointCreationRequest(double x, double y, PointType pointType, const std::vector<int>& connections);
	void handleCarCreationRequest(int pointId, const std::string& carType); // Updated signature
	void handlePointPositionChanged(int id, const QPointF& newPos);
	void handlePointDeletionRequest(int pointId);
	void handleCarDeletionRequest(int carId);
	void handleConnectionDeletion(int startPointId, int endPointId); // New slot
	void handleApplicationExit();
	void setSimulationSpeed(int speed); // New slot for simulation speed

	

signals:
	void simulationUpdated();
	void connectionCreatedInView(int startPointId, int endPointId); // New signal for road creation
	void connectionDeletedInView(int startPointId, int endPointId);
	void carDeletionRequested(int carId);

private:
	Manager manager;
	Workspace* workspace;
	Sidebar* sidebar;

	QTimer* timer; // Change timer to a member variable

	void updateSimulation();
	void updateCarItems(); // New method to update car items

}
;
