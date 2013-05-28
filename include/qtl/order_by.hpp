#ifndef QTL_ORDER_BY
#define QTL_ORDER_BY

#include <vector>
#include <functional>
#include <iterator>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace qtl
{

namespace detail
{

template<typename Range>
struct order_by_vector
{
    typedef typename qtl::const_reference_wrapper<Range>::type reference_wrapper;
    typedef std::vector<reference_wrapper> vector_type;
    typedef typename vector_type::const_iterator iterator_type;
};

}

template<typename Range, typename Func>
class order_by_range : public range<
    order_by_range<Range, Func>, 
    typename detail::order_by_vector<Range>::iterator_type>
{
public:
    typedef typename detail::order_by_vector<Range>::vector_type buffer;
    typedef typename detail::order_by_vector<Range>::iterator_type iterator;

    template<typename R>
    order_by_range(R&& r, Func compare) : 
        range_(std::forward<R>(r)), compare_(compare)
    {

    }

    // const but not thread safe!!
    iterator get_begin() const 
    {         
        execute();
        return buffer_.begin(); 
    }

    // const but not thread safe!!
    iterator get_end() const 
    { 
        execute();
        return buffer_.end(); 
    }

private:
    void execute() const
    {
        if (buffer_.empty())
        {
            for(auto it = range_.begin(), last = range_.end(); it != last; ++it)
                buffer_.push_back(*it);
            std::sort(buffer_.begin(), buffer_.end(), compare_);
        }
    }

    Range range_;
    Func compare_;
    mutable buffer buffer_;
};


template<typename Range>
struct default_order_by
{
    typedef typename detail::order_by_vector<Range>::value_type value_type;
    typedef std::less<value_type> default_compare;
    typedef order_by_range<Range, default_compare> type;

    template<typename R>
    static type create(R&& r)
    {
        return type(std::forward<R>(r), default_compare());
    }
};


template<typename Range, typename Func>
order_by_range<Range, Func> make_order_by_range(Range&& r, Func compare)
{
    return order_by_range<Range, Func>(std::forward<Range>(r), compare);
}

template<typename Range>
typename default_order_by<Range>::type make_order_by_range(Range&& r)
{
    return default_order_by<Range>::create(std::forward<Range>(r));
}


}


#endif  // QTL_ORDER_BY
