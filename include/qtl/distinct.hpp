#ifndef QTL_DISTINCT_HPP
#define QTL_DISTINCT_HPP

#include "range.hpp"
#include "iterator.hpp"
#include <unordered_set>


namespace qtl
{

namespace detail
{
    template<typename Hasher>
    struct hasher_wrapper
    {
        hasher_wrapper() {}
        hasher_wrapper(Hasher h) : hasher(h) {}

        template<typename T>
        size_t operator()(const std::reference_wrapper<T>& ref) const
        {
            return hasher(ref.get());
        }

        template<typename T>
        size_t operator()(const std::reference_wrapper<const T>& ref) const
        {
            return hasher(ref.get());
        }

        template<typename T>
        size_t operator()(T value) const
        {
            return hasher(value);
        }

        Hasher hasher;
    };

    template<typename Range, typename Hasher>
    struct hash_set
    {
        typedef std::unordered_set<
            typename qtl::reference_wrapper<Range>::type,
            hasher_wrapper<Hasher>> type;
    };

    template <typename HashSet>
    size_t default_bucket_count()
    {
      HashSet dummy;
      return dummy.bucket_count();
    }
}

struct distinct_default_hash
{
    template<typename T>
    size_t operator()(const T& ref) const
    {
        return std::hash<T>()(ref);
    }
};

template<typename Iter, typename HashSet>
class distinct_iterator : 
    public base_iterator<Iter, distinct_iterator<Iter, HashSet>>
{
public:
    typedef Iter iterator;
    typedef HashSet hash_set;


    distinct_iterator(iterator it, iterator last, hash_set& seen_elements) :
        iter(it), last(last), seen_elements(seen_elements)
    {
        if (it != last)
            try_add_current();
    }

    void move_next()
    {
        ++iter;
        while(iter != last && !try_add_current())
        {
            ++iter;
        }
    }

    iterator current() const
    {
        return iter;
    }

private:

    bool try_add_current() const
    {
        return seen_elements.insert(*iter).second;
    }


    iterator iter, last;
    hash_set& seen_elements;
};


template<typename Range, typename Hasher>
class distinct_range : public range<
    distinct_range<Range, Hasher>, 
    distinct_iterator<typename Range::iterator, typename detail::hash_set<Range, Hasher>::type>>
{
public:
    typedef typename detail::hash_set<Range, Hasher>::type hash_set;
    typedef distinct_iterator<typename Range::iterator, hash_set> iterator;

    template<typename R>
    distinct_range(R&& r, Hasher hasher) : 
        range(std::forward<R>(r)),
        seen_elements(detail::default_bucket_count<hash_set>(), 
                      hash_set::hasher(hasher)),
        begin_iter(range.begin(), range.end(), seen_elements), 
        end_iter(range.end(), range.end(), seen_elements)
    {
    }

    iterator get_begin() const { return begin_iter; }
    iterator get_end() const { return end_iter; }

private:
    Range range;
    hash_set seen_elements;
    iterator begin_iter, end_iter;
};

template<typename Range>
distinct_range<Range, distinct_default_hash> make_distinct_range(Range&& range)
{
    return distinct_range<Range, distinct_default_hash>(
        std::forward<Range>(range), distinct_default_hash());
}


template<typename Range, typename Hasher>
distinct_range<Range, Hasher> make_distinct_range(Range&& range, Hasher hash)
{
    return distinct_range<Range, Hasher>(
        std::forward<Range>(range), hash);
}

}

#endif  // QTL_DISTINCT_HPP
