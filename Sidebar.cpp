#include "Sidebar.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>

Sidebar::Sidebar(QWidget* parent)
    : QWidget(parent), layout(new QVBoxLayout(this))
{
    setupUI();
}

void Sidebar::setupUI()
{
    startSimulationButton = new QPushButton("Start Simulation", this);
    stopSimulationButton = new QPushButton("Stop Simulation", this);
    simulationSpeedLabel = new QLabel("Simulation Speed:", this);
    simulationSpeedSlider = new QSlider(Qt::Horizontal, this);
    simulationSpeedSlider->setMinimum(1);
    simulationSpeedSlider->setMaximum(5);
    simulationSpeedSlider->setValue(3); // Default to Normal speed

    // Add labels for the slider
    QLabel* slowerLabel = new QLabel("Slower", this);
    QLabel* slowLabel = new QLabel("Slow", this);
    QLabel* normalLabel = new QLabel("Normal", this);
    QLabel* fastLabel = new QLabel("Fast", this);
    QLabel* fasterLabel = new QLabel("Faster", this);

    QHBoxLayout* sliderLabelsLayout = new QHBoxLayout();
    sliderLabelsLayout->addWidget(slowerLabel);
    sliderLabelsLayout->addStretch();
    sliderLabelsLayout->addWidget(slowLabel);
    sliderLabelsLayout->addStretch();
    sliderLabelsLayout->addWidget(normalLabel);
    sliderLabelsLayout->addStretch();
    sliderLabelsLayout->addWidget(fastLabel);
    sliderLabelsLayout->addStretch();
    sliderLabelsLayout->addWidget(fasterLabel);

    QVBoxLayout* sliderLayout = new QVBoxLayout();
    sliderLayout->addWidget(simulationSpeedSlider);
    sliderLayout->addLayout(sliderLabelsLayout);

    QString buttonStyle = "QPushButton {"
        "font-size: 16px;"
        "padding: 10px;"
        "border-radius: 10px;"
        "background-color: #3498db;"
        "color: white;"
        "}"
        "QPushButton:pressed {"
        "background-color: #2980b9;"
        "}";

    startSimulationButton->setStyleSheet(buttonStyle);
    stopSimulationButton->setStyleSheet(buttonStyle);

    QString labelStyle = "QLabel {"
        "font-size: 14px;"
        "color: #2c3e50;"
        "font-weight: bold;"
        "}";
    simulationSpeedLabel->setStyleSheet(labelStyle);
    slowerLabel->setStyleSheet(labelStyle);
    slowLabel->setStyleSheet(labelStyle);
    normalLabel->setStyleSheet(labelStyle);
    fastLabel->setStyleSheet(labelStyle);
    fasterLabel->setStyleSheet(labelStyle);

    QString sliderStyle = "QSlider::groove:horizontal {"
        "border: 1px solid #999999;"
        "height: 8px;"
        "background: #b3b3b3;"
        "border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "background: #3498db;"
        "border: 1px solid #3498db;"
        "width: 18px;"
        "height: 18px;"
        "margin: -5px 0;"
        "border-radius: 9px;"
        "}";

    simulationSpeedSlider->setStyleSheet(sliderStyle);

    layout->addWidget(startSimulationButton);
    layout->addWidget(stopSimulationButton);
    layout->addWidget(simulationSpeedLabel);
    layout->addLayout(sliderLayout);

    setLayout(layout);

    connect(startSimulationButton, &QPushButton::clicked, this, &Sidebar::startSimulationClicked);
    connect(stopSimulationButton, &QPushButton::clicked, this, &Sidebar::stopSimulationClicked);
    connect(simulationSpeedSlider, &QSlider::valueChanged, this, &Sidebar::simulationSpeedChanged); // Connect the slider's value change signal
}
