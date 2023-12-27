#include "fileManager.h"

void readingFiles::readPointsFromFile(const std::string& filename)
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
            for (int i = 0; i < neightbourAmount; i++)
            {
                text >> ticks;
                connections[i]->setTicksToTraverse(ticks);
            }
            for (int i = 0; i < neightbourAmount; i++)
            {
                text >> mas_limit;
                connections[i]->setWeightLimit(mas_limit);
            }
            globalPointFactory.createPoint(id, x, y, connections);
        }
        
    }
}




void readingFiles::readVehiclesFromFile(const std::string& filename)
{

}