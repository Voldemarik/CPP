#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

template <typename... Ts>
class Tuple
{
public:
    constexpr static std::size_t size()
    {
        return sizeof...(Ts);
    }
};

//////////////////////////////////////////////////////////////////

template <typename T, typename... Ts>
class Tuple<T, Ts...>
{
public:
    constexpr Tuple(T &&x, Ts &&...xs)
        : m_head(std::forward<T>(x)),
          m_tail(std::forward<Ts>(xs)...)
    {
    }

    //  ------------------------------------------------

    template <std::size_t I>
    constexpr auto get() const
    {
        if constexpr (I > 0)
        {
            return m_tail.template get<I - 1>();
        }
        else
        {
            return m_head;
        }
    }

    //  ------------------------------------------------

    constexpr static std::size_t size()
    {
        return sizeof...(Ts) + 1;
    }

private:
    T m_head;
    Tuple<Ts...> m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
    static_assert(Tuple<>::size() == 0);
    static_assert(Tuple<int>::size() == 1);
    static_assert(Tuple<int, double>::size() == 2);
    static_assert(Tuple<int, double, std::string>::size() == 3);
    static_assert(Tuple<int, double, std::string, char>::size() == 4);
    static_assert(Tuple<int, double, std::string, char, float>::size() == 5);

    Tuple<int, double, std::string> tuple(1, 2.0, "aaaaa");
    assert(tuple.get<0>() == 1);
    assert(tuple.size() == 3);

    Tuple<> empty_tuple;
    assert(empty_tuple.size() == 0);

    Tuple<int> single_tuple(42);
    assert(single_tuple.size() == 1);

    return 0;
}