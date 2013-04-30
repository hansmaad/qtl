#ifndef QTL_WHERE_HPP
#define QTL_WHERE_HPP

#include "range.hpp"
#include "iterator.hpp"


namespace qtl
{


template<typename Iter, typename Func>
class where_iterator : 
    public base_iterator<Iter, where_iterator<Iter, Func>>
{
public:
    where_iterator(Iter it, Iter last, Func predicate) :
        iter_(it), last_(last), predicate_(predicate)
    {
        while(iter_ != last_ && !predicate_(*iter_))
            ++iter_;
    }

    void move_next()
    {
        ++iter_;
        while(iter_ != last_ && !predicate_(*iter_))
            ++iter_;
    }

    Iter current() const
    {
        return iter_;
    }
private:
    Iter iter_, last_;
    Func predicate_;
};

template<typename Range, typename Func>
class where_range : public range<
    where_range<Range, Func>, 
    where_iterator<typename Range::iterator, Func>>
{
public:
    typedef where_iterator<typename Range::iterator, Func> iterator;

    where_range(Range&& r, Func predicate) : 
        range_(std::move(r)),
        begin_(range_.begin(), range_.end(), predicate), 
        end_(range_.end(), range_.end(), predicate)
    {
    }

    iterator get_begin() const { return begin_; }
    iterator get_end() const { return end_; }

private:
    Range range_;
    iterator begin_, end_;
};


}

#endif  // QTL_WHERE_HPP
