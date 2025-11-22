#include <cassert>
#include <cmath>
#include <compare>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>

class Rational
{
public:
    /* explicit */ Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
    {
        reduce();
    }

    explicit operator double() const
    {
        return 1.0 * m_num / m_den;
    }

    auto &operator+=(Rational const &other)
    {
        auto lcm = std::lcm((long long)m_den, (long long)other.m_den);

        long long new_num = (long long)m_num * (lcm / m_den) + (long long)other.m_num * (lcm / other.m_den);

        m_num = (int)new_num;
        m_den = (int)lcm;

        reduce();

        return *this;
    }

    auto &operator-=(Rational const &other)
    {
        return *this += Rational(other.m_num * -1, other.m_den);
    }

    auto &operator*=(Rational const &other)
    {
        m_num *= other.m_num;
        m_den *= other.m_den;

        reduce();

        return *this;
    }

    auto &operator/=(Rational const &other)
    {
        return *this *= Rational(other.m_den, other.m_num);
    }

    auto const operator++(int)
    {
        auto x = *this;
        *this += 1;
        return x;
    }

    auto const operator--(int)
    {
        auto x = *this;
        *this -= 1;
        return x;
    }

    auto &operator++()
    {
        *this += 1;
        return *this;
    }

    auto &operator--()
    {
        *this -= 1;
        return *this;
    }

    friend auto operator+(Rational lhs, Rational const &rhs) { return lhs += rhs; }

    friend auto operator-(Rational lhs, Rational const &rhs) { return lhs -= rhs; }

    friend auto operator*(Rational lhs, Rational const &rhs) { return lhs *= rhs; }

    friend auto operator/(Rational lhs, Rational const &rhs) { return lhs /= rhs; }

    friend std::strong_ordering operator<=>(Rational const &lhs, Rational const &rhs)
    {
        return (long long)lhs.m_num * rhs.m_den <=> (long long)rhs.m_num * lhs.m_den;
    }

    friend bool operator==(Rational const &lhs, Rational const &rhs)
    {
        return (lhs <=> rhs) == 0;
    }

    friend auto &operator>>(std::istream &stream, Rational &rational)
    {
        return (stream >> rational.m_num).ignore() >> rational.m_den;
    }

    friend auto &operator<<(std::ostream &stream, Rational const &rational)
    {
        return stream << rational.m_num << '/' << rational.m_den;
    }

private:
    void reduce()
    {
        if (m_den < 0)
        {
            m_num = -m_num;
            m_den = -m_den;
        }

        auto gcd = std::gcd((long long)m_num, (long long)m_den);

        m_num = (int)((long long)m_num / gcd);
        m_den = (int)((long long)m_den / gcd);
    }

    int m_num = 0, m_den = 1;
};

auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

int main()
{
    Rational x = 1, y(2, 1);

    std::vector<int> vector_2(5);
    std::vector<int> vector_3 = {1, 2, 3, 4, 5};

    assert(equal(static_cast<double>(x), 1));

    assert((x += y) == Rational(+3, 1));
    assert((x -= y) == Rational(+1, 1));
    assert((x *= y) == Rational(+2, 1));
    assert((x /= y) == Rational(+1, 1));

    assert((x++) == Rational(+1, 1));
    assert((x--) == Rational(+2, 1));
    assert((++y) == Rational(+3, 1));
    assert((--y) == Rational(+2, 1));

    [[maybe_unused]] auto z = 0;

    assert((x + y) == Rational(+3, 1));
    assert((x - y) == Rational(-1, 1));
    assert((x * y) == Rational(+2, 1));
    assert((x / y) == Rational(+1, 2));

    assert((x += 1) == Rational(+2, 1));
    assert((x + 1) == Rational(+3, 1));
    assert((1 + y) == Rational(+3, 1));

    // Тестирование оператора трехстороннего сравнения
    assert((x <=> y) == std::strong_ordering::equal);
    assert((x == y) == true);
    assert((x != y) == false);
    assert((x < y) == false);
    assert((x > y) == false);
    assert((x <= y) == true);
    assert((x >= y) == true);

    Rational a(1, 2), b(1, 3);
    assert((a <=> b) == std::strong_ordering::greater);
    assert((a > b) == true);
    assert((a < b) == false);

    Rational c(2, 4), d(1, 2);
    assert((c <=> d) == std::strong_ordering::equal);
    assert((c == d) == true);

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;

    stream_1 >> x;
    stream_2 << x;

    assert(stream_2.str() == stream_1.str());
}