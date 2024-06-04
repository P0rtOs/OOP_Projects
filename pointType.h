#pragma once
#include <iostream>

enum class PointType {
	PostOffice,
	House,
	Hospital,
	PoliceStation,
	School,
	Last
};


std::ostream& operator<<(std::ostream& os, PointType pointType);