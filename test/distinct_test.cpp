#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"

using qtl::from;

struct DistinctTestFixture
{
    DistinctTestFixture()
    {
    }
};

BOOST_FIXTURE_TEST_SUITE(DistinctTestSuite, DistinctTestFixture)

BOOST_AUTO_TEST_CASE(Distinct_ArrayOfUniqeIntegers)
{
    int values[] = {1, 2, 3, 4};
    auto distinct = from(values).distinct();
    CheckEqualRange(values, distinct);
}

BOOST_AUTO_TEST_SUITE_END()
