#ifndef QTL_ANY_QUERY_HPP
#define QTL_ANY_QUERY_HPP
 
#include "boolean_query.hpp"

namespace qtl
{

template<typename Range, typename Func>
class any_query : public boolean_query<any_query<Range, Func>>
{
public:
    template<typename R>
    any_query(R&& r, Func predicate):
        range(std::forward<R>(r)), predicate(predicate)
    {
    }

    bool boolean_test() const
    {
        for(auto it = begin(range), last = end(range);
            it != last; ++it)
        {
            if (predicate(*it))
                return true;
        }
        return false;
    }

private:
    Range range;
    Func predicate;
};

}
#endif  // QTL_ANY_QUERY_HPP
