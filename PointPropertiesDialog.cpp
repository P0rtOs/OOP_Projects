﻿//#include "PointPropertiesDialog.h"
//
//PointPropertiesDialog::PointPropertiesDialog(PointItem* pointItem, Point* point, QWidget* parent)
//    : QDialog(parent)
//{
//    setupUi(pointItem, point);
//}
//
//void PointPropertiesDialog::setupUi(PointItem* pointItem, Point* point)
//{
//    idLabel = new QLabel(QString("ID: %1").arg(pointItem->getId()), this);
//    xLabel = new QLabel(QString("X: %1").arg(pointItem->getX()), this);
//    yLabel = new QLabel(QString("Y: %1").arg(pointItem->getY()), this);
//
//     Assuming PointClass has similar methods to get ID, X, and Y
//    QLabel* pointIdLabel = new QLabel(QString("Model ID: %1").arg(point->getPointId()), this);
//    QLabel* pointXLabel = new QLabel(QString("Model X: %1").arg(point->getPointX()), this);
//    QLabel* pointYLabel = new QLabel(QString("Model Y: %1").arg(point->getPointY()), this);
//
//    QString pointTypeString;
//    switch (point->getPointType()) {
//    case PointType::PostOffice:
//        pointTypeString = "Post Office";
//        break;
//    case PointType::House:
//        pointTypeString = "House";
//        break;
//    case PointType::Hospital:
//        pointTypeString = "Hospital";
//        break;
//    case PointType::PoliceStation:
//        pointTypeString = "Police Station";
//        break;
//    case PointType::School:
//        pointTypeString = "School";
//        break;
//    default:
//        pointTypeString = "Unknown";
//        break;
//    }
//
//    typeLabel = new QLabel(QString("Type: %1").arg(pointTypeString), this);  // New label for point type
//
//     Create the connections table
//    connectionsTable = new QTableWidget(this);
//    connectionsTable->setColumnCount(3);
//    connectionsTable->setHorizontalHeaderLabels(QStringList() << "Point ID" << "Ticks" << "Weight");
//
//    const auto& neighbors = point->getNeighbors();
//    connectionsTable->setRowCount(neighbors.size());
//    int row = 0;
//    for (const auto& connection : neighbors) {
//        connectionsTable->setItem(row, 0, new QTableWidgetItem(QString::number(connection->getNeighborId())));
//        connectionsTable->setItem(row, 1, new QTableWidgetItem(QString::number(connection->getTicksToTraverse())));
//        connectionsTable->setItem(row, 2, new QTableWidgetItem(QString::number(connection->getWeightLimit())));
//        ++row;
//    }
//
//    QVBoxLayout* layout = new QVBoxLayout(this);
//    layout->addWidget(idLabel);
//    layout->addWidget(xLabel);
//    layout->addWidget(yLabel);
//    layout->addWidget(pointIdLabel);
//    layout->addWidget(pointXLabel);
//    layout->addWidget(pointYLabel);
//    layout->addWidget(typeLabel);
//    layout->addWidget(connectionsTable);
//
//    setLayout(layout);
//    setWindowTitle("Point Properties");
//
//}

#include "PointPropertiesDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

PointPropertiesDialog::PointPropertiesDialog(PointItem* pointItem, Point* point, QWidget* parent)
    : QDialog(parent), pointItem(pointItem), point(point)
{
    setupUI();
}

void PointPropertiesDialog::setupUI()
{
    resize(450, 350);
    layout = new QVBoxLayout(this);

    QLabel* idLabel = new QLabel(QString("Point ID: %1").arg(pointItem->getId()), this);
    QLabel* xLabel = new QLabel(QString("X: %1").arg(pointItem->getX()), this);
    QLabel* yLabel = new QLabel(QString("Y: %1").arg(pointItem->getY()), this);
    PointType arg = point->getPointType();
    QString pointTypeString = "";
    switch (arg) {
    case PointType::PostOffice:
        pointTypeString = "PostOffice";
        break;
    case PointType::House:
        pointTypeString = "House";
        break;
    case PointType::Hospital:
        pointTypeString = "Hospital";
        break;
    case PointType::PoliceStation:
        pointTypeString = "PoliceStation";
        break;
    case PointType::School:
        pointTypeString = "School";
        break;
    default:
        pointTypeString = "UnknownType";
        break;
    }

    QLabel* typeLabel = new QLabel(QString("Type: %1").arg(pointTypeString));

    layout->addWidget(idLabel);
    layout->addWidget(xLabel);
    layout->addWidget(yLabel);
    layout->addWidget(typeLabel);

    QLabel* connectionsLabel = new QLabel("Connections:");
    layout->addWidget(connectionsLabel);

    connectionsTable = new QTableWidget(this);
    connectionsTable->setColumnCount(4);
    connectionsTable->setHorizontalHeaderLabels(QStringList() << "Point ID" << "Ticks" << "Weight" << "Delete");

    const auto& neighbors = point->getNeighbors();
    connectionsTable->setRowCount(neighbors.size());
    int row = 0;
    for (const auto& connection : neighbors) {
        addConnectionRow(connection->getNeighborId(), connection->getTicksToTraverse(), connection->getWeightLimit(), row);
        ++row;
    }

    layout->addWidget(connectionsTable);
    setLayout(layout);
    setWindowTitle("Point Properties");

    QString dialogStyle = "QDialog {"
        "background-color: #ecf0f1;"
        "border-radius: 10px;"
        "}";

    QString labelStyle = "QLabel {"
        "font-size: 14px;"
        "color: #2c3e50;"
        "font-weight: bold;"
        "}";

    QString tableStyle = "QTableWidget {"
        "border: 1px solid #bdc3c7;"
        "border-radius: 5px;"
        "background-color: #ffffff;"
        "}"
        "QHeaderView::section {"
        "background-color: #bdc3c7;"
        "border: 1px solid #bdc3c7;"
        "}";

    QString buttonStyle = "QPushButton {"
        "font-size: 14px;"
        "padding: 5px 10px;"
        "border-radius: 5px;"
        "background-color: #e74c3c;"
        "color: white;"
        "}"
        "QPushButton:pressed {"
        "background-color: #c0392b;"
        "}";

    this->setStyleSheet(dialogStyle);
    idLabel->setStyleSheet(labelStyle);
    xLabel->setStyleSheet(labelStyle);
    yLabel->setStyleSheet(labelStyle);
    typeLabel->setStyleSheet(labelStyle);
    connectionsLabel->setStyleSheet(labelStyle);
    connectionsTable->setStyleSheet(tableStyle);
}

void PointPropertiesDialog::addConnectionRow(int connectionId, int ticksToTraverse, double weightLimit, int row)
{
    QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(connectionId));
    QTableWidgetItem* ticksItem = new QTableWidgetItem(QString::number(ticksToTraverse));
    QTableWidgetItem* weightItem = new QTableWidgetItem(QString::number(weightLimit));

    connectionsTable->setItem(row, 0, idItem);
    connectionsTable->setItem(row, 1, ticksItem);
    connectionsTable->setItem(row, 2, weightItem);

    QPushButton* deleteButton = new QPushButton("Delete");
    deleteButton->setStyleSheet("QPushButton {"
        "font-size: 14px;"
        "padding: 5px 10px;"
        "border-radius: 5px;"
        "background-color: #e74c3c;"
        "color: white;"
        "}"
        "QPushButton:pressed {"
        "background-color: #c0392b;"
        "}");
    connect(deleteButton, &QPushButton::clicked, [this, connectionId]() {
        emit connectionDeletionRequested(pointItem->getId(), connectionId);
        });

    connectionsTable->setCellWidget(row, 3, deleteButton);
}