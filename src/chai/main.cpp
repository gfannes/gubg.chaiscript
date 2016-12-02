#include "chaiscript/chaiscript.hpp"
#include "chaiscript/chaiscript_stdlib.hpp"
#include <iostream>
using namespace chaiscript;
using namespace std;

int main(int argc, const char **argv)
{
    if (argc != 2)
    {
        cout << "You have to pass a chaiscript" << endl;
        return -1;
    }

    using Parser = parser::ChaiScript_Parser<eval::Noop_Tracer, optimizer::Optimizer_Default>;
    chaiscript::ChaiScript_Basic chai(Std_Lib::library(), std::make_unique<Parser>());

    const auto &filename = argv[1];
    chai.eval_file(filename);
    return 0;
}
