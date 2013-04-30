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
    explicit empty_query(Range&& r):
        range_(std::move(r))
    {
    }

    bool boolean_test() const
    {
        return begin(range_) == end(range_);
    }

private:
    Range range_;
};

}

#endif  // QTL_EMPTY_QUERY_HPP
