#ifndef SF_CIRCLE_HPP
#define SF_CIRCLE_HPP


#include "sf_base.hpp"
#include "sf_point.hpp"


namespace ser_fw_test
{

class Circle : public Point
{
public:
    Circle() = default;
    Circle(const std::string& a_name, double a_x, double a_y, unsigned int a_radius);

    virtual ser_fw::Types::ParamsMap TransformTo() const override;
    virtual void TransformFrom(const ser_fw::Types::ParamsMap& a_paramsMap) override;
    virtual std::string TypeName() const override { return "Circle"; }

    // For visual testing:
    void Print() const { std::cout <<  "Circle " << m_name << ": " << "(" << X() << ", " << Y() << "), radius: " << m_radius << "\n"; }
private:
    unsigned int m_radius;
};

} // ser_fw_test


#endif // SF_CIRCLE_HPP