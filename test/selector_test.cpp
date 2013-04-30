#include <array>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"
#include "selector.hpp"

using qtl::from;
using qtl::raw_pointer;
using qtl::pointer;


struct SelectorTestFixture
{};

BOOST_FIXTURE_TEST_SUITE(SelectorTestSuite, SelectorTestFixture)


BOOST_AUTO_TEST_CASE(RawPointer_UniquePtr_ReturnsRawPtr)
{
    typedef std::unique_ptr<int> iptr;

    std::array<iptr, 2> input = { 
        iptr(new int(1)),
        iptr(new int(2)) };

    auto query = from(input).select(raw_pointer());
    std::vector<const int*> result(begin(query), end(query));
    BOOST_CHECK(result.at(0) == input[0].get());
}

BOOST_AUTO_TEST_CASE(Pointer_IntArray_ReturnsPointer)
{

    std::array<int, 2> input = {1, 2};

    auto query = from(input).select(pointer());
    std::vector<const int*> result(begin(query), end(query));
    BOOST_CHECK(result.at(0) == &input[0]);
}

BOOST_AUTO_TEST_SUITE_END()