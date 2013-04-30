#include <type_traits>
#include <functional>

struct foo
{
    template<typename Func, typename Arg>
    static void bar(Func predicate, Arg param)
    {
        typedef typename std::result_of<Func(Arg)>::type result_type;
        predicate(param);
    }
};

int main(int, char*[])
{
    auto f = [] (int x) { return x; };
    
    foo::bar(f, (int)5);
    
    return 0;
}
