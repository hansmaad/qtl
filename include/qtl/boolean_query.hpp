#ifndef BOOLEAN_QUERY_HPP
#define BOOLEAN_QUERY_HPP

namespace qtl
{


template <typename Derived>
class boolean_query 
{
    // Implementation of the safe bool idiom
protected:
    typedef void (boolean_query::*bool_type)() const;
    void const_mem_func() const {}

    boolean_query() {}
    boolean_query(const boolean_query&) {}
    boolean_query& operator=(const boolean_query&) {return *this;}
    ~boolean_query() {}

public:
    operator bool_type() const 
    {
      return (static_cast<const Derived*>(this))->boolean_test()
        ? &boolean_query::const_mem_func : 0;
    }
};

// disable comparison
template <typename T, typename U> 
void operator==(const boolean_query<T>& lhs, const boolean_query<U>& rhs) 
{
    lhs.const_mem_func();	
    return false;
}

template <typename T,typename U> 
void operator!=(const boolean_query<T>& lhs, const boolean_query<U>& rhs) 
{
    lhs.const_mem_func();
    return false;	
}

}


#endif  // BOOLEAN_QUERY_HPP
