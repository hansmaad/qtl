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


BOOST_AUTO_TEST_SUITE_END()
