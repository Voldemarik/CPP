#include <array>
#include <cmath>

constexpr double abs_val(double x)
{
    return x < 0 ? -x : x;
}

constexpr double calcE(double epsilon)
{
    double sum = 1.0;
    double term = 1.0;
    int n = 1;

    while (term > epsilon)
    {
        term /= n;
        sum += term;
        n++;
    }

    return sum;
}

int main()
{
    constexpr std::array<double, 5> epsilons = {
        1e-1, 1e-2, 1e-3, 1e-4, 1e-5};

    constexpr double E_REFERENCE = 2.718281828459045;

    static_assert(abs_val(calcE(epsilons[0]) - E_REFERENCE) < epsilons[0]);
    static_assert(abs_val(calcE(epsilons[1]) - E_REFERENCE) < epsilons[1]);
    static_assert(abs_val(calcE(epsilons[2]) - E_REFERENCE) < epsilons[2]);
    static_assert(abs_val(calcE(epsilons[3]) - E_REFERENCE) < epsilons[3]);
    static_assert(abs_val(calcE(epsilons[4]) - E_REFERENCE) < epsilons[4]);

    return 0;
}