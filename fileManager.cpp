#include "fileManager.h"


void handlePointCreation(int id, int x, int y, const std::vector<int>& neighborIds, const std::vector<int>& ticks, const std::vector<int>& weights) {
    // Створюємо смарт-поінтер
    auto point = std::make_unique<Point>(id, x, y);

    // Додаємо до нього Connections
    for (size_t i = 0; i < neighborIds.size(); ++i) {
        point->addConnection(neighborIds[i], ticks[i], weights[i]);
    }

    /*std::cout << "id:" << id << " " << x << " " << y;
    for (size_t i = 0; i < neighborIds.size(); i++) {
        std::cout << " N id " << point->getNeighbors()[i]->getNeighborId()
            << " ticks: " << point->getNeighbors()[i]->getTicksToTraverse()
            << " weight: " << point->getNeighbors()[i]->getWeightLimit() << std::endl;
    }*/

    // Записуємо у менеджер
    globalPointManager.addPoint(std::move(point));  // Передаємо у власність менеджеру
}

void readingFiles::readPointsFromFile(const std::string& filename) {
    std::ifstream file("points_pack_1.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] != '#') continue;

        std::istringstream iss(line.substr(1));

        int id, x, y, numberOfConnections;
        iss >> id >> x >> y >> numberOfConnections;

        std::vector<int> neighborIds(numberOfConnections);
        std::vector<int> ticks(numberOfConnections);
        std::vector<int> weights(numberOfConnections);

        for (int& neighborId : neighborIds) {
            iss >> neighborId;
        }

        for (int& tick : ticks) {
            iss >> tick;
        }

        for (int& weight : weights) {
            iss >> weight;
        }

        handlePointCreation(id, x, y, neighborIds, ticks, weights);
    }
}

