#include <array>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"

using qtl::from;

struct OrderByTestFixture
{};

BOOST_FIXTURE_TEST_SUITE(OrderByTestSuite, OrderByTestFixture)


BOOST_AUTO_TEST_CASE(OrderBy_312Default_Is123)
{
    std::array<int, 3> input = {3, 1, 2};
    std::array<int, 3> expected = {1, 2, 3};
    auto query = from(input).order_by(std::less<int>());
    CheckEqualRange(expected, query);
}

BOOST_AUTO_TEST_CASE(OrderBy_Sequence)
{    
    std::array<int, 3> expected = {3, 2, 1};
    auto query = from(1).to(3).order_by(std::greater<int>());
    CheckEqualRange(expected, query);
}

BOOST_AUTO_TEST_SUITE_END()
