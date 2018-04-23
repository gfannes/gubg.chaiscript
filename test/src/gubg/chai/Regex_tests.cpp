#include "catch.hpp"
#include "gubg/chai/Regex.hpp"
#include <string>

TEST_CASE("gubg::chai::Regex tests", "[ut][chai][Regex]")
{
    using namespace gubg::chai;

    bool should_pass = true;

    using RegexPtr = std::shared_ptr<Regex>;
    RegexPtr r;

    SECTION("positive")
    {
        should_pass = true;
        SECTION("ctor") { r.reset(new Regex("abc")); }
        SECTION("copy")
        {
            Regex src("abc");
            r.reset(new Regex(src));
        }
        SECTION("assignment")
        {
            r.reset(new Regex());
            r->assign("abc");
        }
    }
    SECTION("negative")
    {
        should_pass = false;
        SECTION("ctor") { r.reset(new Regex()); }
        SECTION("copy")
        {
            Regex src;
            r.reset(new Regex(src));
        }
    }

    REQUIRE(r->matches("abc"));
}
