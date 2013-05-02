#ifndef QTL_SEQUENCE_HPP
#define QTL_SEQUENCE_HPP

#include <iterator>

namespace qtl
{

template<typename T>
class sequence_iterator : 
    public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T, T>
{
public:
    typedef sequence_iterator<T> my_iter;

    T increment_, current_, end_;

    sequence_iterator(T current, T last, T increment) :
         increment_(increment), current_(current), end_(last)
    {

    }

    T operator*() const
    {    
        return current_;
    }

    bool operator==(const my_iter& other) const
    {    
        return current_ == other.current_;
    }

    bool operator!=(const my_iter& other) const
    {    
        return (!(*this == other));
    }

    my_iter& operator++()
    {    
        current_ += increment_;
        adjust();
        return *this;
    }

    my_iter operator++(int)
    {    
        my_iter tmp = *this;
        ++*this;
        return tmp;
    }

    void set_increment(T inc)
    {
        increment_ = inc;
    }

private:
    void adjust()
    {
        if (increment_ > 0 && current_ > end_)
        {
            current_ = end_;
            return;
        }
        if (increment_ < 0 && current_ < end_)
            current_ = end_;
    }

};

template<typename T>
struct sequence : public range<sequence<T>, sequence_iterator<T>>
{
    typedef sequence_iterator<T> iterator;
    typedef sequence<T> my_sequence;

    sequence(iterator first, iterator last) : 
        first(first), last(last)
    {}

    sequence(sequence&& other) : 
        first(other.first), last(other.last)
    {}

    my_sequence increment(T inc) const
    {
        my_sequence s(first, last);
        s.first.set_increment(inc);
        s.last.set_increment(inc);
        return s;
    }

    iterator get_begin() const { return first; }
    iterator get_end() const { return last; }
private:
    iterator first, last;
};


template<typename T>
class sequence_generator
{
    T from;
public:
    sequence_generator(T from) : from(from) 
    {}

    sequence<T> to(T to)
    {
        T end = to > from ? to + T(1) : to - T(1);
        return sequence<T>(
            sequence_iterator<T>(from, end, T(1)),
            sequence_iterator<T>(end, end, T(1)));
    }
};

inline sequence_generator<int> from(int n)
{
    return sequence_generator<int>(n);
}

inline sequence_generator<float> from(float n)
{
    return sequence_generator<float>(n);
}

inline sequence_generator<double> from(double n)
{
    return sequence_generator<double>(n);
}

}


#endif  // QTL_SEQUENCE_HPP