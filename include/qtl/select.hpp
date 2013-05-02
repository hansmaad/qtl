#ifndef QSL_SELECT_HPP
#define QSL_SELECT_HPP

#include <iterator>
#include <type_traits>
#include "range.hpp"
#include "iterator.hpp"
#include "return_type.hpp"


namespace qtl
{

template<typename Function, typename InputArgument>
struct selector_traits
{
    typedef typename function_traits<Function, InputArgument>::return_type result_type;
};


template<typename Iter, typename Func>
struct selector
{
    typedef typename std::iterator_traits<Iter>::value_type value_type;
    typedef typename selector_traits<Func, value_type>::result_type result_type;

    selector(Func selector) : f(selector) {}
    
    template<typename T>
    result_type operator()(const T& t)
    {
        return f(t);
    }

    Func f;
};



template<typename Iter, typename Selector>
struct select_base_iterator
{
    typedef typename Selector::result_type T;
    typedef std::iterator<std::input_iterator_tag, 
        T, std::ptrdiff_t, T*, T> type;
};

template<typename Iter, typename Func>
class select_iterator : 
    public select_base_iterator<Iter, selector<Iter, Func>>::type
{
public:
    typedef select_iterator<Iter, Func> my_iter;
    typedef typename selector<Iter, Func>::result_type result_type;

    select_iterator(Iter it, Func selector) :
        iter_(it), selector_(selector)
    {

    }

    my_iter& operator++()
    {    
        move_next();
        return *this;
    }

    my_iter operator++(int)
    {    
        my_iter tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const my_iter& other) const
    {    
        return iter_ == other.iter_;
    }

    bool operator!=(const my_iter& other) const
    {    
        return (!(*this == other));
    }

    result_type operator*()
    {
        return selector_(*iter_);
    }

    void move_next()
    {
        ++iter_;
    }

private:
    Iter iter_;
    selector<Iter, Func> selector_;
};

template<typename Range, typename Func>
class select_range : public range<
    select_range<Range, Func>, 
    select_iterator<typename Range::iterator, Func>>
{
public:
    typedef select_iterator<typename Range::iterator, Func> iterator;

    template<typename R>
    select_range(R&& r, Func selector) : 
        begin_(r.begin(), selector),
        end_(r.end(), selector),
        range_(std::forward<R>(r))
    {
    }

    iterator get_begin() const { return begin_; }
    iterator get_end() const { return end_; }

private:
    iterator begin_, end_;
    Range range_;

};



}

#endif  // QSL_SELECT_HPP
