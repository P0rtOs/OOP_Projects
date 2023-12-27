#include "fileManager.h"

/*void readingFiles::readPointsFromFile(const std::string& filename)
{
    char ch;
    int id, x, y, neightbourAmount, readed_int, ticks, mas_limit;
    std::vector<Connection*> connections(5);
    for (int s = 0; s < 5; s++)
    {
        connections[s] = new Connection(-1, -1, -1);
    }

    std::ifstream file("points_pack_1.txt", std::ios::binary);
    //std::ifstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        exit(1);
    }

    std::string readed;
    std::getline(file, readed, '\n');
    
    std::istringstream text(readed);


    while (1)
    {
        ch = file.get();
        if (ch == ' ') { continue; }
        if (ch == '\n') { continue; }
        if (ch == '*') { break; }
        

        if (ch == '#')
        {
            file >> id;
            file >> x;
            file >> y;
            file >> neightbourAmount;

            for (int i = 0; i < neightbourAmount; i++)
            {
                file >> readed_int;
                connections[i]->setNeighborId(readed_int);
            }
            for (int s = 0; s < neightbourAmount; s++)
            {
                text >> ticks;
                connections[s]->setTicksToTraverse(ticks);
            }
            for (int j = 0; j < neightbourAmount; j++)
            {
                text >> mas_limit;
                connections[j]->setWeightLimit(mas_limit);
            }
            globalPointFactory.createPoint(id, x, y, connections, neightbourAmount);
        }
        
    }
}*/

void handlePointCreation(int id, int x, int y, const std::vector<int>& neighborIds, const std::vector<int>& ticks, const std::vector<int>& weights) {
    // Create the Point object (modify according to your Point class constructor)
    Point* point = new Point(id, x, y);

    // Create and add connections
    for (size_t i = 0; i < neighborIds.size(); ++i) {
        point->addNeighbor(neighborIds[i], ticks[i], weights[i]);
    }

    std::cout << "id:" << id << " " << x << " " << y;
    for (int i = 0; i < neighborIds.size(); i++)
    {
        std::cout << " N id " << point->getNeighbors()[i]->getNeighborId() << " ticks: " << point->getNeighbors()[i]->getTicksToTraverse() << " weight: " << point->getNeighbors()[i]->getWeightLimit() << std::endl;
    }
    // Add point to the globalPointManager or other relevant data structures
    globalPointManager.addPoint(point);
}
void readingFiles::readPointsFromFile(const std::string& filename) {
    std::ifstream file("points_pack_1.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] != '#') continue; // Skip non-data lines

        std::istringstream iss(line.substr(1)); // Skip '#'

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

        // Assuming a function to handle the creation of Points and their connections
        // This function should take the ID, coordinates, and a list of connections
        handlePointCreation(id, x, y, neighborIds, ticks, weights);
    }
}






void readingFiles::readVehiclesFromFile(const std::string& filename)
{

}