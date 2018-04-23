#include "gubg/chai/test/Engine.hpp"

namespace gubg { namespace chai { namespace test { 

    EnginePtr create_engine()
    {
        EnginePtr ptr;
        ptr.reset(new Engine(chaiscript::Std_Lib::library(), std::make_unique<Parser>()));
        return ptr;
    }

} } } 
