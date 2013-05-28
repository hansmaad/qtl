#ifndef QTL_TYPE_TRAITS_HPP
#define QTL_TYPE_TRAITS_HPP

#include <type_traits>
#include <iterator>
#include <functional>

namespace qtl
{

template<typename Range>
struct const_reference_wrapper
{
    typedef typename Range::iterator iterator;
    typedef const typename std::iterator_traits<iterator>::reference const_reference;

    typedef typename std::conditional<std::is_reference<const_reference>::value,
        std::reference_wrapper<typename std::remove_reference<const_reference>::type>,
        const_reference>::type type;
};

template<typename Range>
struct reference_wrapper
{
    typedef typename Range::iterator iterator;
    typedef typename std::iterator_traits<iterator>::reference reference;
    
    typedef typename std::conditional<std::is_reference<reference>::value,
        std::reference_wrapper<typename std::remove_reference<reference>::type>,
        reference>::type type;
};

}


#endif  // QTL_TYPE_TRAITS_HPP
