#include "fileManager.h"


void readingFiles::readPointsFromFile(const std::string& filename)
{
    const std::string a = "points_pack_1.txt";
    std::ifstream file(a);
    int id, x, y, readed_int, ticks, mas_limit;
    std::vector<Connection*> connections(5);
    //std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        exit(0);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        char symbol;
        iss >> symbol;

        if (symbol == '#')
        {
            iss >> id >> x >> y;

            int i = 0;
            while (iss >> symbol && symbol != '?')
            {
                iss >> readed_int;
                if (connections.size() == i)
                {
                    connections.resize(i + 5);
                }
                connections[i]->setNeighborId(readed_int);
                i++;
            }

            iss >> ticks;
            iss >> mas_limit;
            for (int s = 0; s < connections.size(); s++)
            {
                connections[s]->setTicksToTraverse(ticks);
                connections[s]->setWeightLimit(mas_limit);
            }
        }

        globalPointFactory.createPoint(id, x, y, connections);
    }



    file.close();
}



void readingFiles::readVehiclesFromFile(const std::string& filename)
{

}