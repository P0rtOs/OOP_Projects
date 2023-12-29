#include "fileManager.h"


void handlePointCreation(int id, int x, int y, const std::vector<int>& neighborIds, const std::vector<int>& ticks, const std::vector<int>& weights) {
    // Prepare connections
    std::vector<std::unique_ptr<Connection>> connections;
    for (size_t i = 0; i < neighborIds.size(); ++i) {
        connections.emplace_back(std::make_unique<Connection>(neighborIds[i], ticks[i], weights[i]));
    }

    // Use PointFactory to create the Point
    auto point = globalPointFactory.createPoint(id, x, y, connections);

    // Add the created Point to the PointManager
    globalPointManager.addPoint(std::move(point));
}


void readingFiles::readPointsFromFile(const std::string& filename) {
    std::ifstream file(filename + ".txt");
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

