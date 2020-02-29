#include <nox/optional.hpp>

#include "catch.hpp"

namespace {

template <typename T>
using Optional = nox::Optional<T>;

struct TestData {
    int n1;
    int n2;
};

}  // namespace

TEST_CASE("Optional constructors work", "[optional][constructors]") {
    SECTION("Check that the variadic constructor works") {
        Optional<TestData> optional{1, 2};
        auto value = optional.value_or(TestData{3, 4});
        REQUIRE(value.n1 == 1);
        REQUIRE(value.n2 == 2);
    }
    /* TODO: reference types are currently broken
    SECTION("Check that reference types work") {
        TestData data{1, 2};
        Optional<TestData &> optional{data};
        TestData alt{3, 4};
        auto value = optional.value_or(alt);
        REQUIRE(value.n1 == 1);
        REQUIRE(value.n2 == 2);
    }
    */
}

TEST_CASE("Optional apply works", "[optional][apply]") {
    auto o1 = Optional<int>{};
    auto o2 = Optional<int>{1};
    SECTION("Check that apply(f) works") {
        bool called = false;
        o1.apply([&called](int) { called = true; });
        REQUIRE(called == false);
        o2.apply([&called](int) { called = true; });
        REQUIRE(called == true);
    }
    SECTION("Check that apply(on_present, on_empty) works") {
        bool r1 = o1.apply([](int) { return true; }, []() { return false; });
        REQUIRE(r1 == false);
        bool r2 = o2.apply([](int) { return true; }, []() { return false; });
        REQUIRE(r2 == true);
    }
}
