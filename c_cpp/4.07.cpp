#include <numeric>

template <int N = 0, int D = 1>
struct Ratio
{
    static_assert(D != 0);

    constexpr static auto num = N;
    constexpr static auto den = D;
};

template <typename R1, typename R2>
struct Sum
{
private:
    constexpr static auto num_raw = R1::num * R2::den + R2::num * R1::den;
    constexpr static auto den_raw = R1::den * R2::den;
    constexpr static auto gcd_val = std::gcd(num_raw, den_raw);

public:
    constexpr static auto num = num_raw / gcd_val;
    constexpr static auto den = den_raw / gcd_val;

    using type = Ratio<num, den>;
};

template <typename R1, typename R2>
using sum = typename Sum<R1, R2>::type;

template <typename R1, typename R2>
struct Sub
{
private:
    using negative_R2 = Ratio<-R2::num, R2::den>;

public:
    using type = typename Sum<R1, negative_R2>::type;
};

template <typename R1, typename R2>
using sub = typename Sub<R1, R2>::type;

template <typename R1, typename R2>
struct Mul
{
private:
    constexpr static auto num_raw = R1::num * R2::num;
    constexpr static auto den_raw = R1::den * R2::den;
    constexpr static auto gcd_val = std::gcd(num_raw, den_raw);

public:
    constexpr static auto num = num_raw / gcd_val;
    constexpr static auto den = den_raw / gcd_val;

    using type = Ratio<num, den>;
};

template <typename R1, typename R2>
using mul = typename Mul<R1, R2>::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2>
struct Div
{
    static_assert(R2::num != 0, "Division by zero");

private:
    using reciprocal_R2 = Ratio<R2::den, R2::num>;

public:
    using type = typename Mul<R1, reciprocal_R2>::type;
};

template <typename R1, typename R2>
using div = typename Div<R1, R2>::type;

template <typename T, typename R = Ratio<1>>
struct Duration
{
    T x = T();

    constexpr Duration() = default;
    constexpr Duration(T value) : x(value) {}
};

template <typename T, typename R>
constexpr auto operator-(const Duration<T, R> &duration)
{
    return Duration<T, R>(-duration.x);
}

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(const Duration<T1, R1> &lhs, const Duration<T2, R2> &rhs)
{
    using ratio_t = Ratio<1, sum<R1, R2>::den>;

    auto x =
        (lhs.x * ratio_t::den / R1::den * R1::num +
         rhs.x * ratio_t::den / R2::den * R2::num);

    return Duration<decltype(x), ratio_t>(x);
}

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator-(const Duration<T1, R1> &lhs, const Duration<T2, R2> &rhs)
{
    return lhs + (-rhs);
}

int main()
{
    using R1 = Ratio<1, 2>;
    using R2 = Ratio<1, 3>;
    using R3 = Ratio<2, 4>;
    using R4 = Ratio<3, 1>;

    static_assert(sum<R1, R2>::num == 5);
    static_assert(sum<R1, R2>::den == 6);

    static_assert(sum<R3, R3>::num == 1);
    static_assert(sum<R3, R3>::den == 1);

    static_assert(sub<R1, R2>::num == 1);
    static_assert(sub<R1, R2>::den == 6);

    static_assert(sub<R4, R1>::num == 5);
    static_assert(sub<R4, R1>::den == 2);

    static_assert(mul<R1, R2>::num == 1);
    static_assert(mul<R1, R2>::den == 6);

    static_assert(mul<R1, R4>::num == 3);
    static_assert(mul<R1, R4>::den == 2);

    static_assert(div<R1, R2>::num == 3);
    static_assert(div<R1, R2>::den == 2);

    static_assert(div<R4, R2>::num == 9);
    static_assert(div<R4, R2>::den == 1);

    static_assert(mul<Ratio<2, 4>, Ratio<2, 4>>::num == 1);
    static_assert(mul<Ratio<2, 4>, Ratio<2, 4>>::den == 4);

    constexpr Duration<int, Ratio<1, 2>> duration_1(1);
    constexpr Duration<int, Ratio<1, 3>> duration_2(2);

    constexpr auto duration_sum = duration_1 + duration_2;
    static_assert(duration_sum.x == 7);

    constexpr auto duration_sub = duration_1 - duration_2;
    static_assert(duration_sub.x == -1);

    constexpr auto duration_neg = -duration_1;
    static_assert(duration_neg.x == -1);

    return 0;
}