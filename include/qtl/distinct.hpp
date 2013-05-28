#ifndef QTL_DISTINCT_HPP
#define QTL_DISTINCT_HPP

#include "range.hpp"
#include "iterator.hpp"

namespace qtl
{

template<typename Iter>
class distinct_iterator : 
    public base_iterator<Iter, distinct_iterator<Iter>>
{
public:
    distinct_iterator(Iter it) :
        iter(it)
    {
    }

    void move_next()
    {
        ++iter;
    }

    Iter current() const
    {
        return iter;
    }
private:
    Iter iter;
};

template<typename Range>
class distinct_range : public range<
    distinct_range<Range>, 
    distinct_iterator<typename Range::iterator>>
{
public:
    typedef distinct_iterator<typename Range::iterator> iterator;

    template<typename R>
    distinct_range(R&& r) : 
        range(std::forward<R>(r)),
        begin_iter(range.begin()), 
        end_iter(range.end())
    {
    }

    iterator get_begin() const { return begin_iter; }
    iterator get_end() const { return end_iter; }

private:
    Range range;
    iterator begin_iter, end_iter;
};

template<typename Range>
distinct_range<Range> make_distinct_range(Range&& range)
{
    return distinct_range<Range>(std::forward<Range>(range));
}

}

#endif  // QTL_DISTINCT_HPP
