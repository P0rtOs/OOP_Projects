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
    QGraphicsScene* getScene() const; 


public slots:
    void createPointAtPosition(const QPointF& pos);
    void createCarAtPoint(PointItem* point);
    void updatePointPosition(int id, const QPointF& newPos);
    void showPointProperties(PointItem* pointItem);
    void showCarProperties(CarItem* carItem);
    void initiateConnection(PointItem* pointItem);
    void completeConnection(PointItem* pointItem);
    void addCar(int id, double x, double y, Vehicle* vehicle); 

    void openPointCreationDialog(const QPointF& pos);
    void openCarCreationDialog(int pointId); 
    void addRoadView(int startPointId, int endPointId);
    void removeRoadView(int startPointId, int endPointId);
    void addPoint(int id, double x, double y, PointType pointType);
    void removeCarItem(int carId); 
    void updateSimulation();

    void redrawScene();

signals:
    void pointCreationRequested(double x, double y, PointType pointType, const std::vector<int>& connections);
    void pointPositionChanged(int pointId, const QPointF& newPos);
    void carCreationRequested(int pointId, const std::string& carType);
    void carDeletionRequested(int carId);
    void roadViewCreationRequested(int startPointId, int endPointId);
    void connectionDeletionRequested(int startPointId, int endPointId);
    void pointDeletionRequested(int pointId);
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
