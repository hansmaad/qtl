#include <array>
#include <string>
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"

using qtl::from;

struct AnyTestFixture
{};

BOOST_FIXTURE_TEST_SUITE(AnyTestSuite, AnyTestFixture)


BOOST_AUTO_TEST_CASE(Any_EmptySequence_IsFalse)
{
    std::string s;
    auto query = from(s).any([](char n) {return true;});
    BOOST_CHECK(!query);
}

BOOST_AUTO_TEST_CASE(Any_TruePredicate_IsTrue)
{
    auto query = from(1).to(3).any([](int n) {return true;});
    BOOST_CHECK(query);
}


BOOST_AUTO_TEST_CASE(Any_FalsePredicate_IsFalse)
{
    auto query = from(1).to(3).any([](int n) {return false;});
    BOOST_CHECK(!query);
}

BOOST_AUTO_TEST_CASE(Any_LastIsTrue_IsFalse)
{
    std::array<std::string, 4> input ={
        "Hi", "My", "No", "Why"};

    auto size_is_three = [](const std::string& s) {return s.size() == 3;};
    auto query = from(input).any(size_is_three);
    BOOST_CHECK(query);
}
BOOST_AUTO_TEST_SUITE_END()