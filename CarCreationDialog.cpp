#include "CarCreationDialog.h"

CarCreationDialog::CarCreationDialog(int carId, int pointId, QWidget* parent)
    : QDialog(parent)
{
    setupUi(carId, pointId);
}

void CarCreationDialog::setupUi(int carId, int pointId)
{
    idLabel = new QLabel(QString("Car ID: %1").arg(carId), this);
    pointLabel = new QLabel(QString("Point ID: %1").arg(pointId), this);

    typeComboBox = new QComboBox(this);
    typeComboBox->addItem("Car", "Car");
    typeComboBox->addItem("Truck", "Truck");
    typeComboBox->addItem("SchoolBus", "SchoolBus");

    createButton = new QPushButton("Create", this);
    cancelButton = new QPushButton("Cancel", this);

    connect(createButton, &QPushButton::clicked, this, &CarCreationDialog::onCreateButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &CarCreationDialog::onCancelButtonClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(idLabel);
    mainLayout->addWidget(pointLabel);
    mainLayout->addWidget(typeComboBox);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Create Car");
}

std::string CarCreationDialog::getSelectedCarType() const
{
    return typeComboBox->currentText().toStdString();
}

void CarCreationDialog::onCreateButtonClicked()
{
    accept();
}

void CarCreationDialog::onCancelButtonClicked()
{
    reject();
}
