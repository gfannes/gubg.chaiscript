#ifndef HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_inject_hpp_ALREADY_INCLUDED

#include "gubg/chai/Regex.hpp"

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
    } 

    template <typename What, typename ChaiEngine>
    void inject(ChaiEngine &eng)
    {
        details::inject(eng, (const What *)nullptr);
    }

} } 

#endif
