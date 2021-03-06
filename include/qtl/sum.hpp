#ifndef QTL_SUM_HPP
#define QTL_SUM_HPP

#include <utility>
#include <numeric>
#include <iterator>


namespace qtl
{

template<typename Range>
class sum_query
{
public:
    typedef typename Range::iterator iterator;
    typedef std::iterator_traits<iterator> iterator_traits;
    typedef typename iterator_traits::value_type result_type;

    template<typename R>
    explicit sum_query(R&& r) :
        range(std::forward<R>(r))
    {
    }

    operator result_type() const
    {
        return std::accumulate(
            begin(range), end(range), default_value());
    }

    result_type default_value() const
    {
        return result_type(0);
    }

private:
    Range range;
};


}

#endif  // QTL_SUM_HPP
