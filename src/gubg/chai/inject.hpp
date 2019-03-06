#ifndef HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED

#include "gubg/chai/Regex.hpp"
#include "gubg/chai/File.hpp"
#include "chaiscript/chaiscript.hpp"
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

namespace gubg { namespace chai { 

    struct Date {};

    namespace details { 
        template <typename ChaiEngine>
        void inject(ChaiEngine &eng, const Regex *)
        {
            eng.add(chaiscript::user_type<Regex>(), "Regex");
            eng.add(chaiscript::constructor<Regex()>(), "Regex");
            eng.add(chaiscript::constructor<Regex(const std::string &)>(), "Regex");
            eng.add(chaiscript::constructor<Regex(const Regex &)>(), "Regex");
            eng.add(chaiscript::fun(&Regex::assign), "assign");
            eng.add(chaiscript::fun(&Regex::matches), "matches");
        }

        template <typename ChaiEngine>
        void inject(ChaiEngine & eng, const std::string *)
        {
            auto to_upper = [](const std::string & str) {
              std::string res(str.size(), '0');

              std::transform(str.begin(), str.end(), res.begin(), [](auto c) { return std::toupper(c); } );
              return res;
            };
            eng.add(chaiscript::fun(to_upper), "to_upper");

            auto gsub = [](const std::string & src_str, const std::string &needle, const std::string &repl) {
                std::string res;

                for (std::string::size_type src_pos = 0; true; )
                {
                    auto needle_pos = src_str.find(needle, src_pos);
                    if (needle_pos == std::string::npos)
                    {
                        res.append(src_str.substr(src_pos));
                        break;
                    }
                    const auto size = needle_pos-src_pos;
                    res.append(src_str.substr(src_pos, size));
                    src_pos += size + needle.size();
                    res.append(repl);
                }

                return res;
            };
            eng.add(chaiscript::fun(gsub), "gsub");

            auto getenv = [](const std::string & str) {
                std::string res;
                auto ptr = std::getenv(str.c_str());
                if (ptr)
                    res = ptr;
                return res;
            };
            eng.add(chaiscript::fun(getenv), "getenv");
        }

        template <typename ChaiEngine>
        void inject(ChaiEngine & eng, const Date *)
        {
            eng.add(chaiscript::fun([]()
            {
                std::ostringstream oss;
                std::time_t result = std::time(nullptr);
                const int size = 100;
                char buffer[size];
                std::strftime(buffer, size, "%Y-%m-%d %H:%M:%S", std::localtime(&result));
                oss << buffer;
                return oss.str();
            }), "date");
        }

        template <typename ChaiEngine>
        void inject(ChaiEngine & eng, const File *)
        {
            eng.add_global(chaiscript::var(File()), "File");

            auto open = [](File f, const std::string & filename, char mode, const std::function<void (chaiscript::Boxed_Value)> & functor)
            {
                switch(mode)
                {
                case 'w':
                    open_and_write(filename, [&](OStream & os) { functor(chaiscript::var(os)); });
                    break;

                case 'r':
                    open_and_read(filename, [&](IStream & os) { functor(chaiscript::var(os)); });
                    break;

                default:
                    throw chaiscript::exception::eval_error("Unknown mode");
                }
            };
            eng.add(chaiscript::fun(open), "open");
            eng.add(chaiscript::user_type<OStream>(), "OStream");
            eng.add(chaiscript::fun(&OStream::operator bool), "good");
            eng.add(chaiscript::user_type<IStream>(), "IStream");
            eng.add(chaiscript::fun(&IStream::operator bool), "good");

            auto each_line = [](File f, const std::string & filename, const std::function<void (chaiscript::Boxed_Value)> & functor)
            {
                std::ifstream ifs;
                ifs.open(filename);
                if(!ifs.good())
                    return false;

                std::string line;
                while(std::getline(ifs, line))
                    functor(chaiscript::var(line));

                ifs.close();
                return true;
            };
            eng.add(chaiscript::fun(each_line), "each_line");

            eng.add(chaiscript::fun([](OStream & os, const std::string & v) {
                        return os << v;
                    }), "<<");

            eng.add(chaiscript::fun([](IStream & is, std::string & v) {
                        return is >> v;
                    }), ">>");
            eng.add(chaiscript::fun(&mkdir), "mkdir");
            eng.add(chaiscript::fun(&exists), "exists");
            eng.add(chaiscript::fun(&join_2), "join");
            eng.add(chaiscript::fun(&join_3), "join");
            eng.add(chaiscript::fun(&join_4), "join");
            eng.add(chaiscript::fun(&join_5), "join");
            eng.add(chaiscript::fun(&join_6), "join");
            eng.add(chaiscript::fun(&join_7), "join");
            eng.add(chaiscript::fun(&join_8), "join");
            eng.add(chaiscript::fun(&join_9), "join");
            eng.add(chaiscript::fun(&join_10), "join");
            eng.add(chaiscript::fun(&absolute), "absolute");
            eng.add(chaiscript::fun(&basename_1), "basename");
            eng.add(chaiscript::fun(&basename_2), "basename");
            eng.add(chaiscript::fun(&dirname), "dirname");
            eng.add(chaiscript::fun(&extname), "extname");
        }
    } 

    template <typename What, typename ChaiEngine>
    void inject(ChaiEngine &eng)
    {
        details::inject(eng, (const What *)nullptr);
    }

} } 

#endif
