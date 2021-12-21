#ifndef SF_ISERIALIZATION_FORMATTER_HPP
#define SF_ISERIALIZATION_FORMATTER_HPP


#include <string>
#include "ser_fw_types.hpp"


namespace ser_fw
{

namespace infra
{

// An interface for all Serialization Formatters.
// A concrete Serialization Formatter should handle an encoding process
// of a Types::ParamsMap, to its unique format representation.
class ISerializationFormatter
{
public:
    virtual ~ISerializationFormatter() = default;
    virtual std::string Encode(const Types::ParamsMap& a_mappedParams) const = 0;
};

} // infra

} // ser_fw


#endif // SF_ISERIALIZATION_FORMATTER_HPP