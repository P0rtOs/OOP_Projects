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

    // Apply styles
    QString dialogStyle = "QDialog {"
        "background-color: #ecf0f1;"
        "border-radius: 10px;"
        "}";

    QString labelStyle = "QLabel {"
        "font-size: 14px;"
        "color: #2c3e50;"
        "font-weight: bold;"
        "}";

    QString comboBoxStyle = "QComboBox {"
        "font-size: 14px;"
        "padding: 5px;"
        "border-radius: 5px;"
        "background-color: #ffffff;"
        "border: 1px solid #bdc3c7;"
        "}";

    QString buttonStyle = "QPushButton {"
        "font-size: 14px;"
        "padding: 5px 10px;"
        "border-radius: 5px;"
        "background-color: #3498db;"
        "color: white;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2980b9;"
        "}";

    this->setStyleSheet(dialogStyle);
    idLabel->setStyleSheet(labelStyle);
    pointLabel->setStyleSheet(labelStyle);
    typeComboBox->setStyleSheet(comboBoxStyle);
    createButton->setStyleSheet(buttonStyle);
    cancelButton->setStyleSheet(buttonStyle);
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
