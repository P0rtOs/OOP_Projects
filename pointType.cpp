#include "pointType.h"

std::ostream& operator<<(std::ostream& os, PointType pointType) {
    switch (pointType) {
    case PointType::PostOffice:
        os << "PostOffice";
        break;
    case PointType::House:
        os << "House";
        break;
    case PointType::Hospital:
        os << "Hospital";
        break;
    case PointType::PoliceStation:
        os << "PoliceStation";
        break;
    case PointType::School:
        os << "School";
        break;
    default:
        os << "UnknownType";
        break;
    }
    return os;
}
