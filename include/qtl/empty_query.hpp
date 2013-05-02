#ifndef QTL_EMPTY_QUERY_HPP
#define QTL_EMPTY_QUERY_HPP

#include <utility>
#include "boolean_query.hpp"

namespace qtl
{

template<typename Range>
class empty_query : public boolean_query<empty_query<Range>>
{
public:
    template<typename R>
    explicit empty_query(R&& r):
        range(std::forward<R>(r))
    {
    }

    bool boolean_test() const
    {
        return begin(range) == end(range);
    }

private:
    Range range;
};

}

#endif  // QTL_EMPTY_QUERY_HPP
