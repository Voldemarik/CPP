#include <limits>

template <int N>
struct Fibonacci
{
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
    static_assert(Fibonacci<N - 1>::value <= std::numeric_limits<int>::max() - Fibonacci<N - 2>::value);
};

template <>
struct Fibonacci<1>
{
    static const int value = 1;
};
template <>
struct Fibonacci<2>
{
    static const int value = 1;
};

template <int N>
constexpr int Fibonacci_v = Fibonacci<N>::value;

int main()
{
    static_assert(Fibonacci_v<1> == 1);
    static_assert(Fibonacci_v<10> == 55);
    static_assert(Fibonacci_v<12> == 144);
    static_assert(Fibonacci_v<20> == 6765);

    return 0;
}