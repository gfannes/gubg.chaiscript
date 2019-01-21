#ifndef HEADER_gubg_chai_File_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_File_hpp_ALREADY_INCLUDED

#include <fstream>
#include "chaiscript/chaiscript.hpp"
#include "gubg/std/filesystem.hpp"
#include "gubg/mss.hpp"

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

inline std::string absolute(File f, const std::string & str)
{
    std::filesystem::path path(str);
    return std::filesystem::absolute(path).string();
}

#define JA const std::string & 
inline std::string join_2(File f, JA a1, JA a2) { return gubg::filesystem::combine(a1, a2).string(); }
inline std::string join_3(File f, JA a1, JA a2, JA a3) { return gubg::filesystem::combine({a1, a2, a3}).string(); }
inline std::string join_4(File f, JA a1, JA a2, JA a3, JA a4) { return gubg::filesystem::combine({a1, a2, a3, a4}).string(); }
inline std::string join_5(File f, JA a1, JA a2, JA a3, JA a4, JA a5) { return gubg::filesystem::combine({a1, a2, a3, a4, a5}).string(); }
inline std::string join_6(File f, JA a1, JA a2, JA a3, JA a4, JA a5, JA a6) { return gubg::filesystem::combine({a1, a2, a3, a4, a5, a6}).string(); }
inline std::string join_7(File f, JA a1, JA a2, JA a3, JA a4, JA a5, JA a6, JA a7) { return gubg::filesystem::combine({a1, a2, a3, a4, a5, a6, a7}).string(); }
inline std::string join_8(File f, JA a1, JA a2, JA a3, JA a4, JA a5, JA a6, JA a7, JA a8) { return gubg::filesystem::combine({a1, a2, a3, a4, a5, a6, a7, a8}).string(); }
inline std::string join_9(File f, JA a1, JA a2, JA a3, JA a4, JA a5, JA a6, JA a7, JA a8, JA a9) { return gubg::filesystem::combine({a1, a2, a3, a4, a5, a6, a7, a8, a9}).string(); }
inline std::string join_10(File f, JA a1, JA a2, JA a3, JA a4, JA a5, JA a6, JA a7, JA a8, JA a9, JA a10) { return gubg::filesystem::combine({a1, a2, a3, a4, a5, a6, a7, a8, a9, a10}).string(); }
#undef JA

inline bool mkdir(File f, const std::string & filename)
{
    return std::filesystem::create_directories(filename);
}

inline bool exists(File f, const std::string & filename)
{
    return std::filesystem::exists(filename);
}

} }

#endif
