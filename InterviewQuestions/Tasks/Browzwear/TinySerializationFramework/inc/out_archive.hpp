#ifndef SF_OUT_ARCHIVE_HPP
#define SF_OUT_ARCHIVE_HPP


#include <string>
#include <memory> // std::shared_ptr
#include <algorithm> // std::for_each
#include <type_traits> // std::is_same
#include "ifile_handler.hpp"
#include "iformatter.hpp"
#include "iser_fw_obj.hpp"


namespace ser_fw
{

// A class that handles writing ISerFwObjs to a data file,
// from a pre-initialized ISerFwObjs Container.
// Concept of IFileHandlerPtr: must be or std::shared_ptr<IFileHandler> or IFileHandlerPtr* type.
// Concept of IFormatterPtr: must be or std::shared_ptr<IFormatter> or IFormatter* type.
template <typename IFileHandlerPtr = std::shared_ptr<infra::IFileHandler>,
            typename IFormatterPtr = std::shared_ptr<infra::IFormatter>>
class OutArchive
{
    static_assert(std::is_same<IFileHandlerPtr, std::shared_ptr<infra::IFileHandler>>::value
        || std::is_same<IFileHandlerPtr, infra::IFileHandler*>::value, "IFileHandlerPtr must be or std::shared_ptr<IFileHandler> or IFileHandler*");

    static_assert(std::is_same<IFormatterPtr, std::shared_ptr<infra::IFormatter>>::value
        || std::is_same<IFormatterPtr, infra::IFormatter*>::value, "IFormatterPtr must be or std::shared_ptr<IFormatter> or IFormatter*");

public:
    OutArchive(const std::string& a_datafile, IFileHandlerPtr a_fileHandler, IFormatterPtr a_formatter);
    OutArchive(const OutArchive& a_other) = default;
    OutArchive& operator=(const OutArchive& a_other) = default;
    ~OutArchive() = default;

    // Concept of C: must be a container that implements begin(), end(), and must define value_type type.
    // C::value_type must be std::shared_ptr<ISerFwObj> or ISerFwObj* type.
    template <typename C>
    void Write(const C& a_serFwObjects) const;

private:
    std::string m_datafile;
    IFileHandlerPtr m_fileHandler;
    IFormatterPtr m_formatter;
};


// Inline implementation:
template <typename IFileHandlerPtr, typename IFormatterPtr>
OutArchive<IFileHandlerPtr,IFormatterPtr>::OutArchive(const std::string& a_datafile, IFileHandlerPtr a_fileHandler, IFormatterPtr a_formatter)
: m_datafile(a_datafile)
, m_fileHandler(a_fileHandler)
, m_formatter(a_formatter)
{
}


template <typename IFileHandlerPtr, typename IFormatterPtr>
template <typename C>
void OutArchive<IFileHandlerPtr,IFormatterPtr>::Write(const C& a_serFwObjects) const
{
    static_assert(std::is_same<typename C::value_type, std::shared_ptr<infra::ISerFwObj>>::value
        || std::is_same<typename C::value_type, infra::ISerFwObj*>::value, "C::value_type must be std::shared_ptr<ISerFwObj> or ISerFwObj*");


    Types::ParsedLinesCollection parsedFormatLines;

    std::for_each(a_serFwObjects.begin(), a_serFwObjects.end(),
    [&](typename C::value_type a_serFwObjPtr)
    {
        parsedFormatLines.push_back(
            m_formatter->Serialize({a_serFwObjPtr->TypeName(), a_serFwObjPtr->ToParamsMap()}));
    });

    m_fileHandler->WriteFile(parsedFormatLines, m_datafile);
}

} // ser_fw


#endif // SF_OUT_ARCHIVE_HPP
