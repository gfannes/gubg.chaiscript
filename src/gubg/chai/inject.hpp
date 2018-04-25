#ifndef HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED

#include "gubg/chai/Regex.hpp"
#include "gubg/chai/File.hpp"
#include "chaiscript/chaiscript.hpp"
#include <string>
#include <fstream>

namespace gubg { namespace chai { 

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
            eng.add(chaiscript::user_type<IStream>(), "IStream");

            eng.add(chaiscript::fun([](OStream & os, const std::string & v) {
                        return os << v;
                    }), "<<");

            eng.add(chaiscript::fun([](IStream & is, std::string & v) {
                        return is >> v;
                    }), ">>");
            eng.add(chaiscript::fun(&mkdir), "mkdir");
        }
    } 

    template <typename What, typename ChaiEngine>
    void inject(ChaiEngine &eng)
    {
        details::inject(eng, (const What *)nullptr);
    }

} } 

#endif
