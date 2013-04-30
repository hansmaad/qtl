#include <array>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <cctype>  // islower
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"
#include "predicate.hpp"

using qtl::from;

struct WhereTestFixture
{};

BOOST_FIXTURE_TEST_SUITE(WhereTestSuite, WhereTestFixture)


BOOST_AUTO_TEST_CASE(Where_TruePredicate_EqualToInput)
{
    std::array<int, 3> input = {1,2,3};
    auto query = from(input).where([](int n) {return true;});
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(Where_FalsePredicate_IsEmpty)
{
    std::array<int, 3> input = {1,2,3};
    auto query = from(input).where([](int n) {return false;});
    BOOST_CHECK(query.empty());
}

BOOST_AUTO_TEST_CASE(Where_From1To5Greater2_Is345)
{
    std::array<int, 3> expected = {3,4,5};
    auto query = from(1).to(5).where(qtl::greater(2));
    CheckEqualRange(expected, query);
}

BOOST_AUTO_TEST_CASE(Where_ConstSequence_ReturnsConstReference)
{
    std::array<int, 3> sequence = {1, 2, 3};
    const std::array<int, 3>& input = sequence;

    auto query = from(input).where([](const int& n) {return true;});
    const int& ref = *begin(query);
    BOOST_CHECK_EQUAL(&ref, &sequence[0]);
}

BOOST_AUTO_TEST_CASE(Where_RangeOfUncopyableTruePredicate_IsEqual)
{
    std::list<uncopyable> input;
    input.emplace_back(1);
    input.emplace_back(2);
    input.emplace_back(3);

    auto query = from(input).where([](const uncopyable& u) {return true;});
    CheckEqualRange(input, query);
}

BOOST_AUTO_TEST_CASE(Where_IstreamIteratorIsUpper_IsUpper)
{
    std::stringstream txt;
    txt << "QueryTemplateLibrary";
    std::istream_iterator<char> a(txt), b;

    auto isupper = [](char c) {return std::isupper(c);};
    auto query = qtl::from(a, b).where(isupper);
    std::string result(begin(query), end(query));
    BOOST_CHECK_EQUAL(result, "QTL");
}

BOOST_AUTO_TEST_SUITE_END()
