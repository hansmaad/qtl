#ifndef QTL_RANGE_HPP
#define QTL_RANGE_HPP

#include <iterator>


#ifdef QTL_HAS_RVALUE_QUALIFIER

#define QTL_RVALUE_QUALIFIER &&
#define QTL_MOVE_THIS std::move(static_cast<T&>(*this))

#else

#define QTL_RVALUE_QUALIFIER 
#define QTL_MOVE_THIS(T) *(static_cast<T*>(this))

#endif


namespace qtl
{


template<typename Range, typename Func>
class where_range;

template<typename Range, typename Func>
class select_range;

template<typename Range, typename Func>
class order_by_range;


template<typename Derived, typename Iter>
class range
{
public:
    range() 
    {}

    range(range&&)
    {}

    template<typename Func>
    where_range<Derived, Func> where(Func predicate) QTL_RVALUE_QUALIFIER
    {
        return where_range<Derived, Func>(move_this(), predicate);
    }

    template<typename Func>
    select_range<Derived, Func> select(Func predicate) QTL_RVALUE_QUALIFIER
    {
        return select_range<Derived, Func>(move_this(), predicate);
    }

    template<typename Func>
    order_by_range<Derived, Func> order_by(Func compare) QTL_RVALUE_QUALIFIER
    {
        return make_order_by_range(move_this(), compare);
    }

    /// @brief  Determines whether all elements of a 
    ///         sequence satisfy a condition.
    /// @param predicate  A function to test each element for a condition.
    /// @returns A boolean_query that converts to true if every element of the 
    //           source sequence passes the test in the specified predicate, 
    //           or if the sequence is empty; otherwise, false.
    template<typename Func>
    all_query<Derived, Func> all(Func predicate) QTL_RVALUE_QUALIFIER
    {
        return all_query<Derived, Func>(move_this(), predicate);
    }

    /// @brief  Determines whether any element of a 
    ///         sequence satisfies a condition.
    /// @param predicate  A function to test each element for a condition.
    /// @returns A boolean_query that converts to true if any element in the
    ///          source sequence pass the test in the specified predicate; 
    ///          otherwise, false.
    template<typename Func>
    any_query<Derived, Func> any(Func predicate) QTL_RVALUE_QUALIFIER
    {
        return any_query<Derived, Func>(move_this(), predicate);
    }

    empty_query<Derived> empty() QTL_RVALUE_QUALIFIER
    {
        return empty_query<Derived>(move_this());
    }

    sum_query<Derived> sum() QTL_RVALUE_QUALIFIER
    {
        return sum_query<Derived>(move_this());
    }

    Iter begin() const
    {
        return static_cast<const Derived*>(this)->get_begin();
    }

    Iter end() const
    {
        return static_cast<const Derived*>(this)->get_end();
    }

protected:     
    Derived move_this() QTL_RVALUE_QUALIFIER
    {
        return QTL_MOVE_THIS(Derived);

    }

private:
    //range(const range&);
    //void operator=(const range&);
};

template<typename Iter>
class iterator_range : public range<iterator_range<Iter>, Iter>
{
public:
    typedef Iter iterator;

    iterator_range(Iter first, Iter last) : begin_(first), end_(last) {}

    iterator_range(iterator_range&& other) :
        begin_(other.begin_), end_(other.end_)
    {}

    Iter get_begin() const { return begin_; }
    Iter get_end() const { return end_; }

private:
    Iter begin_, end_;
};



template<typename Iter>
iterator_range<Iter> make_range(Iter first, Iter last)
{
    return iterator_range<Iter>(first, last);
}

template<typename Derived, typename Iter>
Iter begin(const range<Derived, Iter>& r)
{
    return r.begin();
}

template<typename Derived, typename Iter>
Iter end(const range<Derived, Iter>& r)
{
    return r.end();
}


using std::begin;
using std::end;

template<typename Range>
auto from(const Range& r) -> decltype(make_range(begin(r), end(r)))
{
    return make_range(begin(r), end(r));
}


inline iterator_range<const char*> from(const char* r)
{
    // vc10 fails with std::end for const char* ??
    return iterator_range<const char*>(r, r + strlen(r));
}

template<typename Iter>
iterator_range<Iter> from(Iter first, Iter last)
{
    return make_range(first, last);
}


}
#endif  // QTL_RANGE_HPP
