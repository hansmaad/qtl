
#include <array>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <sstream>
#include <memory>
#include <boost/test/unit_test.hpp>

#include "qtl/qtl.hpp"
#include "test_tools.hpp"

using qtl::from;

struct FromTestFixture
{};

BOOST_FIXTURE_TEST_SUITE(FromTestSuite, FromTestFixture)


BOOST_AUTO_TEST_CASE(From_EmptyRange_IsEmpty)
{
    std::vector<int> input;
    auto query = from(input);
    BOOST_CHECK(query.empty());
}

BOOST_AUTO_TEST_CASE(From_Range_IsEqual)
{
    std::array<int, 3> input = {1, 2, 3};
    auto query = from(input);
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(FromTo_1To3_Equals123)
{
    std::array<int, 3> input = {1, 2, 3};
    auto query = from(1).to(3);
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(FromTo_1point0To3point0_Equals123)
{
    std::array<double, 3> input = {1.0, 2.0, 3.0};
    auto query = from(1.0).to(3.0);
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(FromTo_1To5Inc2_Equals135)
{
    std::array<int, 3> input = {1, 3, 5};
    auto query = from(1).to(5).increment(2);
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(FromTo_5To1IncMinus2_Equals531)
{
    std::array<int, 3> input = {5, 3, 1};
    auto query = from(5).to(1).increment(-2);
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(FromTo_1To3AssignToVector_Equals123)
{
    std::array<int, 3> input = {1, 2, 3};
    auto query = from(1).to(3);
    std::vector<int> v(begin(query), end(query));
    CheckEqualRange(input, v);
}

BOOST_AUTO_TEST_CASE(From_RangeOfUncopyable_IsEqual)
{
    std::list<uncopyable> input;
    input.emplace_back(1);
    input.emplace_back(2);
    input.emplace_back(3);

    auto query = from(input);
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(From_UniquePtrs_IsEqual)
{
    std::array<std::unique_ptr<int>, 2> input = { 
        std::unique_ptr<int>(new int(1)),
        std::unique_ptr<int>(new int(2)) };

    auto query = from(input);
    CheckEqualRange(input, query);
}



BOOST_AUTO_TEST_SUITE_END()
