#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QContextMenuEvent>

class SimulationController;
enum class PointType;
class CarItem;
class Vehicle;
class PointItem;

class Workspace : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Workspace(QWidget* parent);

    void addPoint(int id, double x, double y);
    void addRoad(PointItem* startPoint, PointItem* endPoint);
    QGraphicsScene* getScene() const;  // Getter for the scene


public slots:
    void createPointAtPosition(const QPointF& pos);
    void createCarAtPoint(PointItem* point);
    void updatePointPosition(int id, const QPointF& newPos);
    void showPointProperties(PointItem* pointItem);
    void showCarProperties(CarItem* carItem);  // New slot
    void initiateConnection(PointItem* pointItem);
    void completeConnection(PointItem* pointItem);
    void addCar(int id, double x, double y, Vehicle* vehicle);  // Updated signature

    void openPointCreationDialog(const QPointF& pos);  // New slot for opening the dialog
    void openCarCreationDialog(int pointId);  // New slot for opening the car creation dialog
    void addRoadView(int startPointId, int endPointId);
    void removeRoadView(int startPointId, int endPointId);  // Slot for removing a road view  // New slot
    void addPoint(int id, double x, double y, PointType pointType);
    void removeCarItem(int carId);  // Add this slot declaration
    void updateSimulation();  // Add this slot to update the simulation view

signals:
    void pointCreationRequested(double x, double y, PointType pointType, const std::vector<int>& connections);
    void pointPositionChanged(int pointId, const QPointF& newPos);
    void carCreationRequested(int pointId, const std::string& carType);  // Updated signal for car creation
    void carDeletionRequested(int carId);  // Signal for car deletion
    void roadViewCreationRequested(int startPointId, int endPointId);  // New signal for road creation
    void connectionDeletionRequested(int startPointId, int endPointId);  // New signal for connection deletion
    void pointDeletionRequested(int pointId);  // Signal for point deletion
    void simulationUpdated();

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void drawBackground(QPainter* painter, const QRectF& rect) override;

    

private:
    QGraphicsScene* scene;
    void setupScene();

    QPoint lastMousePos;
    bool panning;
    double minScaleFactor;
    double maxScaleFactor;

    QPixmap backgroundImage;
    bool isBackgroundLoaded = false;

    PointItem* firstPointForConnection = nullptr;
};
