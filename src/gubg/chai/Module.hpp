#ifndef HEADER_gubg_chai_Module_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_Module_hpp_ALREADY_INCLUDED

#include <memory>

namespace chaiscript {

struct Module;

}

namespace cook { namespace view { namespace chai {

    using ModulePtr = std::unique_ptr<chaiscript::Module>;

} } }

#endif
