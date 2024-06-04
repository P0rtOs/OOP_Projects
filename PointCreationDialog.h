#pragma once

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pointType.h"

class Point;
class QTableWidget;

class PointCreationDialog : public QDialog
{
    Q_OBJECT

public:
    PointCreationDialog(int pointId, double x, double y, const std::vector<Point*>& nearestPoints, QWidget* parent = nullptr);

    PointType getSelectedPointType() const;
    std::vector<int> getSelectedConnections() const;

private:
    QLabel* idLabel;
    QLabel* coordLabel;
    QComboBox* typeComboBox;
    QTableWidget* connectionsTable;
    QPushButton* createButton;
    QPushButton* cancelButton;

    void setupUi(int pointId, double x, double y, const std::vector<Point*>& nearestPoints);

private slots:
    void onCreateButtonClicked();
    void onCancelButtonClicked();
};
