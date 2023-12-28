#pragma once
#include "fileManager.h"
#include "pointClass.h"
#include "vehicleClass.h"

class Manager
{
private:
    Ticker ticker;
    readingFiles readingInterface;
public:
    Manager() = default;
    ~Manager() = default;
    void startTestSimulation();
    void endSimulation();
};