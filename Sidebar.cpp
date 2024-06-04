#include "Sidebar.h"
#include <QPushButton>
#include <QVBoxLayout>

Sidebar::Sidebar(QWidget* parent)
    : QWidget(parent), layout(new QVBoxLayout(this))
{
    setupUI();
}

void Sidebar::setupUI()
{
    /*createPointButton = new QPushButton("Create Point", this);
    createVehicleButton = new QPushButton("Create Vehicle", this);
    createConnectionButton = new QPushButton("Create Connection", this);*/
    startSimulationButton = new QPushButton("Start Simulation", this);
    stopSimulationButton = new QPushButton("Stop Simulation", this);

    /*layout->addWidget(createPointButton);
    layout->addWidget(createVehicleButton);
    layout->addWidget(createConnectionButton);*/
    layout->addWidget(startSimulationButton);
    layout->addWidget(stopSimulationButton);

    setLayout(layout);

    /*connect(createPointButton, &QPushButton::clicked, this, &Sidebar::createPointClicked);
    connect(createVehicleButton, &QPushButton::clicked, this, &Sidebar::createVehicleClicked);
    connect(createConnectionButton, &QPushButton::clicked, this, &Sidebar::createConnectionClicked);*/
    connect(startSimulationButton, &QPushButton::clicked, this, &Sidebar::startSimulationClicked);
    connect(stopSimulationButton, &QPushButton::clicked, this, &Sidebar::stopSimulationClicked);
}
