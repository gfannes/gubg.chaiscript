#ifndef HEADER_gubg_chai_test_Engine_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_test_Engine_hpp_ALREADY_INCLUDED

#include "chaiscript/chaiscript.hpp"
#include <memory>

namespace gubg { namespace chai { namespace test { 

    using Parser = chaiscript::parser::ChaiScript_Parser<chaiscript::eval::Noop_Tracer, chaiscript::optimizer::Optimizer_Default>;
    using Engine = chaiscript::ChaiScript_Basic;
    using EnginePtr = std::shared_ptr<Engine>;

    EnginePtr create_engine();

} } } 

#endif
