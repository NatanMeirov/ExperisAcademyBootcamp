#include "sf_point.hpp"
#include <string> // std::stof, std::to_string
#include "sf_base.hpp"


namespace ser_fw_test
{

Point::Point(const std::string& a_name, double a_x, double a_y)
: Base(a_name)
, m_x(a_x)
, m_y(a_y)
{
}


ser_fw::Types::ParamsMap Point::ToParamsMap() const
{
    ser_fw::Types::ParamsMap map;
    map.insert({"name", m_name});
    map.insert({"x", std::to_string(m_x)});
    map.insert({"y", std::to_string(m_y)});

    return map;
}


void Point::FromParamsMap(const ser_fw::Types::ParamsMap& a_paramsMap)
{
    *this = Point(a_paramsMap.at("name"), std::stof(a_paramsMap.at("x")), std::stof(a_paramsMap.at("y")));
}

} // ser_fw_test
