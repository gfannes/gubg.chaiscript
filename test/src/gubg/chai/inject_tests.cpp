#include "catch.hpp"
#include "gubg/chai/test/Engine.hpp"
#include "gubg/chai/inject.hpp"
#include <string>

TEST_CASE("gubg::chai::inject tests", "[ut][chai][Regex]")
{
    using namespace gubg::chai;

    test::EnginePtr ptr = gubg::chai::test::create_engine();
    REQUIRE(!!ptr);
    auto &engine = *ptr;

    inject<Regex>(engine);

    std::string script;

    SECTION("default ctor")
    {
        script.append(R"chai(auto r = Regex(); true)chai");
    }
    SECTION("ctor from string")
    {
        script.append(R"chai(auto r = Regex("a.b.c"); true)chai");
    }
    SECTION("copy")
    {
        script.append(R"chai(auto r = Regex(); auto copy = r; true)chai");
    }
    SECTION("matches for simple full string")
    {
        script.append(R"chai(auto r = Regex("abc"); r.matches("abc"))chai");
    }
    SECTION("matches for simple partial string")
    {
        script.append(R"chai(auto r = Regex("b"); r.matches("abc"))chai");
    }
    SECTION("matches for partial string with decimals")
    {
        script.append(R"chai(auto r = Regex("v\\d"); r.matches("a/v1/bc"))chai");
    }
    SECTION("assign")
    {
        script.append(R"chai(auto r = Regex(); r.assign("abc"); r.matches("abc"))chai");
    }

    bool ok = engine.eval<bool>(script);
    REQUIRE(ok);
}
