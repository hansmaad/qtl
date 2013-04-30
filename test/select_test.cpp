#include <array>
#include <vector>
#include <iterator>
#include <string>
#include <map>
#include <boost/test/unit_test.hpp>
#include "test_tools.hpp"
#include "qtl/qtl.hpp"

using qtl::from;

struct SelectTestFixture
{
    SelectTestFixture()
    {
        input123[0] = 1;
        input123[1] = 2;
        input123[2] = 3;
    }

    template<typename Func>
    void TestResultIsEqualToInput(Func f)
    {
        auto query = from(input123).select(f);
        CheckEqualRange(query, input123);
    }

    std::array<int, 3> input123;
};

BOOST_FIXTURE_TEST_SUITE(SelectTestSuite, SelectTestFixture)


BOOST_AUTO_TEST_CASE(Select_1To3TrivialSelect_Is123)
{
    auto query = from(input123).select([](int n) {return n;});
    CheckEqualRange(input123, query);
}

BOOST_AUTO_TEST_CASE(Select_1To3SelectNegative_IsNegative123)
{
    std::array<int, 3> expected = {-1, -2, -3};
    auto query = from(1).to(3).select([](int n) {return -n;});
    CheckEqualRange(expected, query);
}

BOOST_AUTO_TEST_CASE(Select_1To3SelectSquared_Is149)
{
    std::array<int, 3> expected = {1, 4, 9};
    auto query = from(1).to(3).select([](int n) -> int {return n*n;});
    CheckEqualRange(expected, query);
}

BOOST_AUTO_TEST_CASE(Select_Map567To123SelectValue_Is123)
{
    std::map<int, int> m;
    m[5] = 1;
    m[6] = 2;
    m[7] = 3;

    auto query = from(m).select(
        [](const std::pair<int, int>& p) {return p.second;});
    CheckEqualRange(input123, query);
}

BOOST_AUTO_TEST_CASE(Select_CreateVectorOfMultiplesOf3_Is369)
{
    std::array<int, 3> expected = {3, 6, 9};
    auto query = from(1).to(3).select([](int n) -> int {return 3*n;});
    std::vector<int> result(begin(query), end(query));
    CheckEqualRange(expected, result);
}

int Trivial(int i) 
{ 
    return i; 
}

BOOST_AUTO_TEST_CASE(Select_UseFreeFunction_Is123)
{
    TestResultIsEqualToInput(Trivial);
}

BOOST_AUTO_TEST_CASE(Select_NonConstFunctor_Is123)
{
    struct FunctorType{
        int operator()(int n) {return n;}
    } NonConstFunctor;
    TestResultIsEqualToInput(NonConstFunctor);
}

BOOST_AUTO_TEST_CASE(Select_ConstFunctor_Is123)
{
    struct FunctorType{
        int operator()(int n) const {return n;}
    } ConstFunctor;
    TestResultIsEqualToInput(ConstFunctor);
}

BOOST_AUTO_TEST_CASE(Select_OverloadedFunctor_Is123)
{
    struct FunctorType{
        int operator()(int n) const {return n;}
        int operator()(int n) {return n;}
    } Functor;
    TestResultIsEqualToInput(Functor);
}

BOOST_AUTO_TEST_CASE(Select_ConstReferenceFunctor_Is123)
{
    struct FunctorType{
        int operator()(const int& n) const {return n;}
    } Functor;
    TestResultIsEqualToInput(Functor);
}

BOOST_AUTO_TEST_SUITE_END()
