#include <array>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"

#include "qtl/qtl.hpp"
#include "qtl/predicate.hpp"

using qtl::from;

struct PredicateTestFixture
{
    template<typename Query>
    std::string StringFromQuery(Query query)
    {
        return std::string(begin(query), end(query));
    }
};

BOOST_FIXTURE_TEST_SUITE(PredicateTestSuite, PredicateTestFixture)


BOOST_AUTO_TEST_CASE(IsAlpha_IsAZaz_ReturnTrue)
{
   for(char c  = 'a'; c <= 'z'; ++c)
       BOOST_CHECK(qtl::is_alpha(c));
}

BOOST_AUTO_TEST_CASE(IsAlpha_UsedInWhere_ReturnsAlphaCharsOnly)
{
    const char* text = "Hello World!";
    auto result = StringFromQuery(from(text).where(qtl::is_alpha));
    BOOST_CHECK_EQUAL(result, "HelloWorld");
}

BOOST_AUTO_TEST_CASE(OrPredicate_IsAlphaOrIsAlpha_ReturnsHelloWorld)
{
    using qtl::is_alpha;
    const char* text = "Hello World!";
    auto result = StringFromQuery(from(text).where(is_alpha.or(is_alpha)));
    BOOST_CHECK_EQUAL(result, "HelloWorld");
}

BOOST_AUTO_TEST_CASE(OrOperator_IsAlphaOrIsWhitespace_ReturnsHello_World)
{
    using qtl::is_alpha;
    using qtl::is_whitespace;
    const char* text = "Hello World!";
    auto result = StringFromQuery(from(text).where(is_alpha | is_whitespace));
    BOOST_CHECK_EQUAL(result, "Hello World");
}


BOOST_AUTO_TEST_SUITE_END()
