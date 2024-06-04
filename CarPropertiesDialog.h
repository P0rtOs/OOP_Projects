#pragma once

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include "CarItem.h"
#include "vehicleClass.h"

class CarPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    CarPropertiesDialog(CarItem* carItem, Vehicle* vehicle, QWidget* parent = nullptr);

public slots:
    void updateCarProperties();

private:
    QLabel* idLabel;
    QLabel* typeLabel;
    QLabel* currentPointLabel;
    QLabel* locationStateLabel;
    QLabel* roadTargetLabel;
    QTableWidget* pathTable;

    CarItem* carItem;
    Vehicle* vehicle;
};
