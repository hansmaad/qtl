#include <array>
#include <string>
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"

using qtl::from;

struct SumTestFixture
{
};

BOOST_FIXTURE_TEST_SUITE(SumTestSuite, SumTestFixture)


BOOST_AUTO_TEST_CASE(Sum_EmptyIntSequence_Is0)
{
    std::string empty;
    auto query = from(empty).sum();
    char sum = query;
    BOOST_CHECK_EQUAL(sum, 0);
}

BOOST_AUTO_TEST_SUITE_END()
