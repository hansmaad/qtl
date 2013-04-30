#ifndef QTL_PREDICATE_HPP
#define QTL_PREDICATE_HPP

#include <locale>


namespace qtl
{

template<typename LeftPredicate, typename RightPredicate>
struct or_predicate;

template<typename Derived>
struct predicate
{
    template<typename T>
    bool operator()(T value) const
    {
        return static_cast<const Derived*>(this)->is_satisfied_by(value);
    }

    template<typename Predicate>
    or_predicate<Derived, Predicate> or(Predicate predicate);

protected:
    ~predicate()
    {
    }
};

template<typename LeftPredicate, typename RightPredicate>
or_predicate<LeftPredicate, RightPredicate> operator |(
    const LeftPredicate& left, const RightPredicate& right)
{
    return or_predicate<LeftPredicate, RightPredicate>(left, right);
}

template<typename LeftPredicate, typename RightPredicate>
struct or_predicate : public predicate<or_predicate<LeftPredicate, RightPredicate>>
{
    or_predicate(LeftPredicate left_predicate, RightPredicate right_predicate) :
        left_predicate(left_predicate), right_predicate(right_predicate)
    {
    }

    template<typename CharType>
    bool is_satisfied_by(CharType value) const
    {
        return left_predicate(value) ||
            right_predicate(value);
    }

    LeftPredicate left_predicate;
    RightPredicate right_predicate;
};

template<typename Derived>
template<typename Predicate>
or_predicate<Derived, Predicate> predicate<Derived>::or(Predicate predicate)
{
    return or_predicate<Derived, Predicate>(
        *static_cast<Derived*>(this), predicate);
}

struct is_alpha_predicate : public predicate<is_alpha_predicate>
{
    template<typename CharType>
    bool is_satisfied_by(CharType value) const
    {
        return std::isalpha(value, std::locale(""));
    }
};

struct is_whitespace_predicate : public predicate<is_whitespace_predicate>
{
    template<typename CharType>
    bool is_satisfied_by(CharType value) const
    {
        return std::isspace(value, std::locale(""));
    }
};

static is_whitespace_predicate is_whitespace;
static is_alpha_predicate is_alpha;




template<typename T>
struct greater_predicate
{
    greater_predicate(const T& value) : value_(value) {}
    bool operator()(const T& t) const
    {
        return t > value_;
    }
    T value_;
};

template<typename T>
inline greater_predicate<T> greater(const T& value)
{
    return greater_predicate<T>(value);
}

}

#endif  // QTL_PREDICATE_HPP
