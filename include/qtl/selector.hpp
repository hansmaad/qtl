#ifndef QTL_SELECTOR_HPP
#define QTL_SELECTOR_HPP

namespace qtl
{

struct raw_ptr_selector
{
    template<typename T>
    const T* operator()(const std::unique_ptr<T>& p) const
    {
        return p.get();
    }
    template<typename T>
    const T* operator()(const std::shared_ptr<T>& p) const
    {
        return p.get();
    }
    template<typename T>
   const  T* operator()(const std::weak_ptr<T>& p) const
    {
        return p.get();
    }
};

template<typename T>
struct selector_traits<raw_ptr_selector, T>
{
    typedef const T* result_type;
};

template<typename T>
struct selector_traits<raw_ptr_selector, std::unique_ptr<T>>
{
    typedef const T* result_type;
};

struct ptr_selector
{
    template<typename T>
    const T* operator()(const T& p) const
    {
        return &p;
    }
};

template<typename T>
struct selector_traits<ptr_selector, T>
{
    typedef const T* result_type;
};

inline ptr_selector pointer()
{
    return ptr_selector();
}

inline raw_ptr_selector raw_pointer()
{
    return raw_ptr_selector();
}


}

#endif  // QTL_SELECTOR_HPP
