#pragma once

#include <QThread>
#include "fileManagerClass.h"
#include "pointClass.h"
#include "vehicleClass.h"
#include "tickerClass.h"

class Manager : public QThread
{
    Q_OBJECT

public:
    Manager() = default;
    ~Manager() = default;
    void run() override;
    void startSimulation();
    void endSimulation();
    Ticker& getTicker();  // New method to get the Ticker reference

private:
    Ticker ticker;
    readingFiles readingInterface;
    bool running = false;
};
