#ifndef QTL_RETURN_TYPE_HPP
#define QTL_RETURN_TYPE_HPP

#define HAS_RESULTOF_LAMBDA 1

#ifdef HAS_RESULTOF_LAMBDA
#include <type_traits>
#endif

namespace qtl
{

template <typename R, typename C> R return_type_const(R (C::*)() const);
template <typename R, typename C> R return_type(R (C::*)());
template <typename R, typename C> R return_type(R (C::*)() const);
template <typename R, typename C, typename A> R return_type_const(R (C::*)(A) const);
template <typename R, typename C, typename A> R return_type(R (C::*)(A));
template <typename R, typename C, typename A> R return_type(R (C::*)(A) const);


#ifdef HAS_RESULTOF_LAMBDA

template<typename Functor, typename InputArgument>
struct function_traits
{
    typedef typename std::result_of<Functor(InputArgument)>::type return_type;
};

#else

template<typename Functor, typename InputArgument>
struct function_traits
{
    typedef decltype(return_type(&Functor::operator())) return_type;
};

template<typename ReturnType, typename Argument, typename Input>
struct function_traits<ReturnType(*)(Argument), Input>
{
    typedef ReturnType return_type;
};

#endif


}

#endif  // QTL_RETURN_TYPE_HPP
