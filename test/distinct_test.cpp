#include <boost/test/unit_test.hpp>
#include <list>
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

BOOST_AUTO_TEST_CASE(Distinct_ArrayOfUniqueIntegers)
{
    int values[] = {1, 2, 3, 4};
    auto distinct = from(values).distinct();
    CheckEqualRange(values, distinct);
}


BOOST_AUTO_TEST_CASE(Distinct_ArrayOfIntegers)
{
    int values[] = {1, 2, 2, 3, 4};
    int expected[] = {1, 2, 3, 4};
    auto distinct = from(values).distinct();
    CheckEqualRange(expected, distinct);
}

BOOST_AUTO_TEST_CASE(Distinct_1stElementDouble)
{
    int values[] = {1, 1, 2, 2, 3, 4};
    int expected[] = {1, 2, 3, 4};
    auto distinct = from(values).distinct();
    CheckEqualRange(expected, distinct);
}


BOOST_AUTO_TEST_CASE(Distinct_String)
{
    std::string text = "Hello    World  ";
    auto distinct = from(text).distinct();
    BOOST_CHECK_EQUAL("Helo Wrd", 
        std::string(begin(distinct), end(distinct)));
}

struct Person { 
    Person(std::string n) : name(n) {}

    std::string name; 
};

inline bool operator==(const Person& lh, const Person& rh) {
    return lh.name == rh.name;
}

BOOST_AUTO_TEST_CASE(Distinct_Person)
{
    std::list<Person> persons;
    persons.push_back(Person("Joe"));
    persons.push_back(Person("Jack"));
    persons.push_back(Person("Joe"));
    
    auto person_hash = [](const Person& p) { return std::hash<std::string>()(p.name); };
    auto distinct = from(persons).distinct(person_hash);
    std::vector<Person> result(begin(distinct), end(distinct));
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK_EQUAL(result.at(0).name, "Joe");
    BOOST_CHECK_EQUAL(result.at(1).name, "Jack");
}

BOOST_AUTO_TEST_CASE(Distinct_Sequence)
{
    auto distinct = from(1).to(5).distinct();
    int expected[] = {1, 2, 3, 4, 5};
    CheckEqualRange(expected, distinct);
}

BOOST_AUTO_TEST_SUITE_END()
