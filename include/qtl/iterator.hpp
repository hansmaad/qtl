#ifndef QTL_ITERATOR_HPP
#define QTL_ITERATOR_HPP

#include <iterator>
#include "type_traits.hpp"

namespace qtl
{

template<typename Iter>
struct forward_iterator
{
    typedef typename std::iterator_traits<Iter>::reference reference;
    typedef typename std::iterator_traits<Iter>::value_type value_type; 
    typedef std::iterator<std::input_iterator_tag, value_type> type;
};


template<typename Iter, typename Derived>
class base_iterator : public forward_iterator<Iter>::type
{
public:
    typedef base_iterator<Iter, Derived> my_iter;

    typedef typename std::iterator_traits<Iter>::reference reference;
    typedef const reference const_reference;


    my_iter& operator++()
    {    
        Derived* d = static_cast<Derived*>(this);
        d->move_next();
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
        return static_cast<const Derived&>(*this).current() == 
            static_cast<const Derived&>(other).current();
    }

    bool operator!=(const my_iter& other) const
    {    
        return (!(*this == other));
    }

    const_reference operator*() const
    {
        return *static_cast<const Derived*>(this)->current();
    }

};

}


#endif  // QTL_ITERATOR_HPP
