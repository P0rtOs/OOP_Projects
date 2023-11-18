#pragma once
#include "vehicleManager.h"
#include <fstream>
#include <sstream>

std::vector<Point> readPointsFromFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);

    if (file.is_open()) {
        int pointId;
        double pointX, pointY;

       
        file.close();
    }

    return points;
}
class fileManager {
    private:
        int chosenFilesNumber;
        bool isReadAlready;

};

