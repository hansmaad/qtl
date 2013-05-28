#ifndef TEST_TOOLS_HPP
#define TEST_TOOLS_HPP

#include <ostream>
#include <memory>

class uncopyable
{
    uncopyable(uncopyable&);
    uncopyable(uncopyable&&);
    void operator=(uncopyable&);
    void operator=(uncopyable&&);
public:
    uncopyable(int i) : n(i) {}
    bool operator==(const uncopyable& other) const
    {
        return n == other.n;
    }
    int n;
};

inline std::ostream& operator<<(std::ostream& os, const uncopyable& u)
{
    return os << u.n;
}

template<typename T>
inline std::ostream& operator<<(
    std::ostream& os, const std::unique_ptr<T>& ptr)
{
    return os << *ptr;
}

template<typename Iter1, typename Iter2>
bool Equal(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for(;;)
    {
        if(first1 == last1)
            return first2 == last2;
        else if (first2 == last2)
            return false;
        if (!(*first1 == *first2))
            return false;
        ++first1; ++first2;
    }
    return true;
}

template<typename Iter1, typename Iter2>
std::string MakeRangeMessage(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    using std::begin;
    using std::end;
    std::ostringstream s;
    s << "[... ";
    for(;first1 != last1; ++first1)
        s << *first1 << ";";
    s << "] != [... ";
    for(;first2 != last2; ++first2)
        s << *first2 << ";";
    s << "]";
    return s.str();
}


template<typename Iter1, typename Iter2>
void CheckEqualRange(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for(;;)
    {
        if(first1 == last1)
        {
            BOOST_CHECK_MESSAGE(first2 == last2, "Ranges don't match in size");
            return;
        }
        else if (first2 == last2)
            BOOST_FAIL("Ranges don't match in size");
        if (!(*first1 == *first2))
            BOOST_FAIL(MakeRangeMessage(first1, last1, first2, last2));
        ++first1; ++first2;
    }
}

template<typename Range1, typename Range2>
void CheckEqualRange(const Range1& r1, const Range2& r2)
{
    using std::begin;
    using std::end;

    CheckEqualRange(begin(r1), end(r1), begin(r2), end(r2));
}


#endif  // TEST_TOOLS_HPP
