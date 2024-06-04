#pragma once

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include "PointItem.h"
#include "pointClass.h"

class PointPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    PointPropertiesDialog(PointItem* pointItem, Point* point, QWidget* parent = nullptr);

signals:
    void connectionDeletionRequested(int startPointId, int endPointId);

private:
    QTableWidget* connectionsTable;

    PointItem* pointItem;
    Point* point;
    QVBoxLayout* layout;
    std::vector<std::pair<int, int>> connections;  // To store connection pairs

    void setupUI();
    void addConnectionRow(int connectionId, int ticksToTraverse, double weightLimit, int row);
    void addConnectionRow(int connectionId, int ticksToTraverse, double weightLimit);
};
