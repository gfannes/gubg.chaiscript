#ifndef HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED

#include "gubg/chai/Regex.hpp"
#include "chaiscript/chaiscript.hpp"
#include <string>

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
    } 

    template <typename What, typename ChaiEngine>
    void inject(ChaiEngine &eng)
    {
        details::inject(eng, (const What *)nullptr);
    }

} } 

#endif
