#pragma once

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "vehicleClass.h"

class CarCreationDialog : public QDialog
{
    Q_OBJECT

public:
    CarCreationDialog(int carId, int pointId, QWidget* parent = nullptr);

    std::string getSelectedCarType() const;

private:
    QLabel* idLabel;
    QLabel* pointLabel;
    QComboBox* typeComboBox;
    QPushButton* createButton;
    QPushButton* cancelButton;

    void setupUi(int carId, int pointId);

private slots:
    void onCreateButtonClicked();
    void onCancelButtonClicked();
};
