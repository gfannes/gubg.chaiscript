#ifndef HEADER_gubg_chai_File_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_File_hpp_ALREADY_INCLUDED

#include <fstream>
#include "chaiscript/chaiscript.hpp"
#include "gubg/std/filesystem.hpp"

namespace gubg { namespace chai {

struct File {};
struct OStream
{
    OStream(std::ostream * oss) : oss_(oss) {}
    operator bool() const { return oss_ && oss_->good(); }

    std::ostream * oss_;
};

struct IStream
{
    IStream(std::istream * iss) : iss_(iss) {}

    operator bool() const { return iss_ && iss_->good(); }
    std::istream * iss_;
};

OStream & operator<<(OStream & str, const std::string & value)
{
    if (str)
        (*str.oss_) << value;

    return str;
}

IStream & operator>>(IStream & str, std::string & value)
{
    if (str)
        std::getline(*str.iss_, value);
    return str;
}


inline void open_and_write(const std::string & filename, std::function<void (OStream&)> functor)
{
    std::ofstream ofs;
    ofs.open(filename);

    {
        OStream os(&ofs);
        functor(os);
    }
    ofs.close();
}

inline void open_and_read(const std::string & filename, std::function<void (IStream&)> functor)
{
    std::ifstream ifs;
    ifs.open(filename);

    {
        IStream is(&ifs);
        functor(is);
    }
    ifs.close();;
}

bool mkdir(File f, const std::string & filename)
{
    return std::filesystem::create_directories(filename);
}

} }

#endif
