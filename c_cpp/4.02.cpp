#include <cassert>
#include <cmath>

template <typename T>
T calculate_max(T head) { return head; }

template <typename T, typename... Tail>
T calculate_max(T head, Tail... tail)
{
    T max_of_tail = calculate_max(tail...);
    return head < max_of_tail ? max_of_tail : head;
}

template <typename T>
T calculate_min(T head) { return head; }

template <typename T, typename... Tail>
T calculate_min(T head, Tail... tail)
{
    T min_of_tail = calculate_min(tail...);
    return head > min_of_tail ? min_of_tail : head;
}

//////////////////////////////////////////////////////////////////////////////////////

auto calculate_sum(auto... xs) { return (xs + ...); }

auto calculate_average(auto... xs) { return (xs + ...) / sizeof...(xs); }

//////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    double d1 = 10.5, d2 = 2.0, d3 = 8.0, d4 = 15.5;

    assert(equal(calculate_max(d1, d2), 10.5));
    assert(equal(calculate_max(d1, d2, d3, d4), 15.5));

    assert(equal(calculate_min(d1, d2), 2.0));
    assert(equal(calculate_min(d1, d2, d3, d4), 2.0));

    assert(equal(calculate_sum(d1, d2), 12.5));
    assert(equal(calculate_sum(d1, d2, d3, d4), 36.0));

    assert(equal(calculate_average(d1, d2), 6.25));

    assert(equal(calculate_average(d1, d2, d3, d4), 9.0));
}