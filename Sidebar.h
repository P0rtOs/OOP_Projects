#pragma once

#include <QLabel>
#include <QWidget>


class QSlider;
class QPushButton;
class QVBoxLayout;

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget* parent = nullptr);

signals:
    void createPointClicked();
    void createVehicleClicked();
    void createConnectionClicked();
    void startSimulationClicked();
    void stopSimulationClicked();
    void simulationSpeedChanged(int speed);


private:
    QVBoxLayout* layout;
    QPushButton* createPointButton;
    QPushButton* createVehicleButton;
    QPushButton* createConnectionButton;
    QPushButton* startSimulationButton;
    QPushButton* stopSimulationButton;
    QSlider* simulationSpeedSlider;
    QLabel* simulationSpeedLabel;

    void setupUI();
};
