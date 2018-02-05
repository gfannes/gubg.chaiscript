#ifndef HEADER_gubg_chai_ModuleFwd_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_ModuleFwd_hpp_ALREADY_INCLUDED

#include <memory>

namespace chaiscript {

struct Module;

}

namespace gubg { namespace chai {

using ModulePtr = std::unique_ptr<chaiscript::Module>;

} }

#endif
