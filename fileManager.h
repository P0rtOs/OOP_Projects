#pragma once

#include "vehicleManager.h"
#include "connectionClass.h"
#include "pointFactory.h"

#include <iostream>
#include <fstream>
#include <sstream>

//TODO Дописати конструктор для поінта з ініціалізацією всіх полів. Перевірити правильність зчитування 
// Додати створення точки менеджером після зчитування даних.
class readingFiles
{
    void readDataFromFile(const std::string& filename)
    {
        const std::string a = "TEST1.txt";
        std::ifstream file(a);
        int id, x, y, readed_int, ticks, mas_limit;
        std::vector<Connection*> connections;
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

             
        }

        file.close();
    }
};


