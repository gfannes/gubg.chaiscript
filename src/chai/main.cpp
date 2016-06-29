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
    ChaiScript chai(Std_Lib::library());
    const auto &filename = argv[1];
    chai.eval_file(filename);
    return 0;
}
