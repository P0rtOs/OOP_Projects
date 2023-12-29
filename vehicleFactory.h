#pragma once
#include <iostream>
#include <vector>
#include <utility>


class Vehicle;

class VehicleFactory
{
public:
    VehicleFactory() = default;
    ~VehicleFactory() = default;
    Vehicle* createVehicle(int id, std::string type);
};
