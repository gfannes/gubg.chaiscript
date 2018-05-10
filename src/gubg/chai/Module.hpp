#ifndef HEADER_gubg_chai_Module_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_Module_hpp_ALREADY_INCLUDED

#include "gubg/chai/ModuleFwd.hpp"
#include "chaiscript/chaiscript.hpp"

namespace gubg { namespace chai {

    inline ModulePtr make_module() { return std::make_unique<chaiscript::Module>(); }

} }

#endif
