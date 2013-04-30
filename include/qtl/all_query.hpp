#ifndef QTL_ALL_QUERY_HPP
#define QTL_ALL_QUERY_HPP
 
#include "boolean_query.hpp"

namespace qtl
{

template<typename Range, typename Func>
class all_query : public boolean_query<all_query<Range, Func>>
{
public:
    explicit all_query(Range&& r, Func predicate):
        range_(std::move(r)), predicate_(predicate)
    {
    }

    bool boolean_test() const
    {
        for(auto it = begin(range_), last = end(range_);
            it != last; ++it)
        {
            if (!predicate_(*it))
                return false;
        }
        return true;
    }

private:
    Range range_;
    Func predicate_;
};

}
#endif  // QTL_ALL_QUERY_HPP
