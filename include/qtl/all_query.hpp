#ifndef QTL_ALL_QUERY_HPP
#define QTL_ALL_QUERY_HPP
 
#include "boolean_query.hpp"

namespace qtl
{

template<typename Range, typename Func>
class all_query : public boolean_query<all_query<Range, Func>>
{
public:
    template<typename R>
    all_query(R&& r, Func predicate):
        range(std::forward<R>(r)), predicate(predicate)
    {
    }

    bool boolean_test() const
    {
        for(auto it = begin(range), last = end(range);
            it != last; ++it)
        {
            if (!predicate(*it))
                return false;
        }
        return true;
    }

private:
    Range range;
    Func predicate;
};

}
#endif  // QTL_ALL_QUERY_HPP
