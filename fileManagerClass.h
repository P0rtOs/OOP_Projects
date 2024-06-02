#pragma once

#include "vehicleManagerClass.h"
#include "connectionClass.h"
#include "pointFactoryClass.h"
#include "GlobalObjects.h"


#include <iostream>
#include <fstream>
#include <sstream>

// Додати створення точки після зчитування даних.
class readingFiles
{
public:
    void readPointsFromFile(const std::string& filename);

    //void readVehiclesFromFile(const std::string& filename);
};


