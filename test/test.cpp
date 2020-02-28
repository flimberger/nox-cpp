#include <nox/optional.hpp>

#include "catch.hpp"

TEST_CASE("Optional apply works", "[optional][apply]") {
    auto o1 = nox::Optional<int>{};
    auto o2 = nox::Optional<int>{1};
    SECTION("apply(f)") {
        bool called = false;
        o1.apply([&called](int) { called = true; });
        REQUIRE(called == false);
        o2.apply([&called](int) { called = true; });
        REQUIRE(called == true);
    }
    SECTION("apply(on_present, on_empty)") {
        bool r1 = o1.apply([](int) { return true; }, []() { return false; });
        REQUIRE(r1 == false);
        bool r2 = o2.apply([](int) { return true; }, []() { return false; });
        REQUIRE(r2 == true);
    }
}
