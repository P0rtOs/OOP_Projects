#include "CarPropertiesDialog.h"

CarPropertiesDialog::CarPropertiesDialog(CarItem* carItem, Vehicle* vehicle, QWidget* parent)
    : QDialog(parent), carItem(carItem), vehicle(vehicle)
{
    idLabel = new QLabel(QString("ID: %1").arg(carItem->getId()), this);
    typeLabel = new QLabel(QString("Type: %1").arg(QString::fromStdString(vehicle->getVehicleType())), this);
    currentPointLabel = new QLabel(QString("Current Point: %1").arg(vehicle->getCurrentPointId()), this);
    locationStateLabel = new QLabel(QString("Location State: %1").arg(vehicle->getLocationState() == Vehicle::AT_POINT ? "At Point" : "On Road"), this);

    if (vehicle->getLocationState() == Vehicle::ON_ROAD) {
        roadTargetLabel = new QLabel(QString("On Road To Point: %1").arg(vehicle->getCurrentRoad()->getNeighborId()), this);
    }
    else {
        roadTargetLabel = new QLabel(QString("On Road To Point: N/A"), this);
    }

    // Create the path table
    pathTable = new QTableWidget(this);
    pathTable->setColumnCount(1);
    pathTable->setHorizontalHeaderLabels(QStringList() << "Path Point IDs");

    const auto& path = vehicle->getPath();
    pathTable->setRowCount(path.size());
    int row = 0;
    for (const auto& point : path) {
        pathTable->setItem(row, 0, new QTableWidgetItem(QString::number(point->getPointId())));
        ++row;
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(idLabel);
    layout->addWidget(typeLabel);
    layout->addWidget(currentPointLabel);
    layout->addWidget(locationStateLabel);
    layout->addWidget(roadTargetLabel);
    layout->addWidget(pathTable);

    setLayout(layout);
    setWindowTitle("Car Properties");

    updateCarProperties();  // Initial update
}

void CarPropertiesDialog::updateCarProperties()
{
    idLabel->setText(QString("ID: %1").arg(carItem->getId()));
    typeLabel->setText(QString("Type: %1").arg(QString::fromStdString(vehicle->getVehicleType())));
    currentPointLabel->setText(QString("Current Point: %1").arg(vehicle->getCurrentPointId()));
    locationStateLabel->setText(QString("Location State: %1").arg(vehicle->getLocationState() == Vehicle::AT_POINT ? "At Point" : "On Road"));

    if (vehicle->getLocationState() == Vehicle::ON_ROAD) {
        roadTargetLabel->setText(QString("On Road To Point: %1").arg(vehicle->getCurrentRoad()->getNeighborId()));
    }
    else {
        roadTargetLabel->setText("On Road To Point: N/A");
    }

    pathTable->clearContents();
    const auto& path = vehicle->getPath();
    pathTable->setRowCount(path.size());
    for (int row = 0; row < path.size(); ++row) {
        pathTable->setItem(row, 0, new QTableWidgetItem(QString::number(path[row]->getPointId())));
    }
}
