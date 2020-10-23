#ifndef HEADER_gubg_chai_Time_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_Time_hpp_ALREADY_INCLUDED

#include <string>
#include <functional>
#include <unordered_map>
#include <gubg/std/filesystem.hpp>
#include <gubg/file/system.hpp>
#include <gubg/hash/MD5.hpp>

namespace gubg { namespace chai {

    struct Time {};

    template <typename T>
    void visit_files(const std::filesystem::path & p, T && func)
    {
        if (is_regular_file(p))
            func(p);
        else if (is_directory(p))
        {
            for(const auto & f : std::filesystem::recursive_directory_iterator(p))
            {
                if (is_regular_file(f))
                    func(f);
            }
        }
    }

    inline hash::md5::Hash make_hash(const std::filesystem::path &f)
    {
        std::string content;
        if (file::read(content, f))
        {
            hash::md5::Stream s;
            s<< content;
            return s.hash();
        }
        return {};
    }


    inline void protect(Time t, const std::string &path, std::function<void()> functor)
    {
        using key_type = std::filesystem::path;
        using value_type = std::pair<hash::md5::Hash, std::filesystem::file_time_type>;

        // construct a map with:
        //  * keys: a file under path
        //  * values: md5sum and access time information for that file
        std::unordered_map<key_type, value_type> entries;
        visit_files(path, [&](const std::filesystem::path &f) {
            entries[f] = std::make_pair(make_hash(f), last_write_time(f));
        });

        // call the functor
        functor();

        // restore the write times
        visit_files(path, [&](const std::filesystem::path &f) {
            auto it = entries.find(f);
            if (it != entries.end() && make_hash(f) == it->second.first)
                last_write_time(f, it->second.second);
        });
    }

} }

#endif

