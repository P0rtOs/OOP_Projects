#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QContextMenuEvent>

class PointItem;

class Workspace : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Workspace(QWidget* parent = nullptr);

    void addPoint(int id, double x, double y);
    void addRoad(PointItem* startPoint, PointItem* endPoint);
    void addCar(int id, double x, double y);


public slots:
    void createPointAtPosition(const QPointF& pos);
    void createCarAtPoint(PointItem* point);
    void updatePointPosition(int id, const QPointF& newPos);

signals:
    void pointCreationRequested(double x, double y);
    void pointPositionChanged(int pointId, const QPointF& newPos);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QGraphicsScene* scene;
    void setupScene();

    QPoint lastMousePos;
    bool panning;
    double minScaleFactor;
    double maxScaleFactor;

};
