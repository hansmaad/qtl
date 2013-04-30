#include <array>
#include <string>
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"

using qtl::from;

struct AllTestFixture
{};

BOOST_FIXTURE_TEST_SUITE(AllTestSuite, AllTestFixture)


BOOST_AUTO_TEST_CASE(All_EmptySequence_IsTrue)
{
    auto query = from(1).to(1).all([](int n) {return true;});
    BOOST_CHECK(query);
}

BOOST_AUTO_TEST_CASE(All_TruePredicate_IsTrue)
{
    auto query = from(1).to(3).all([](int n) {return true;});
    BOOST_CHECK(query);
}


BOOST_AUTO_TEST_CASE(All_FalsePredicate_IsFalse)
{
    auto query = from(1).to(3).all([](int n) {return false;});
    BOOST_CHECK(!query);
}

BOOST_AUTO_TEST_CASE(All_LastIsFalse_IsFalse)
{
    std::array<std::string, 4> input ={
        "Hi", "My", "No", "Why"};

    auto size_is_two = [](const std::string& s) {return s.size() == 2;};
    auto query = from(input).all(size_is_two);
    BOOST_CHECK(!query);
}
BOOST_AUTO_TEST_SUITE_END()