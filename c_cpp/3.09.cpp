#include <cstdint>
#include <iostream>
#include <array>
#include <sstream>
#include <cassert>
#include <string>

class IPv4
{
public:
    IPv4() : address{0, 0, 0, 0} {}

    IPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : address{a, b, c, d} {}

    IPv4 &operator++()
    {
        increment();
        return *this;
    }

    IPv4 operator++(int)
    {
        IPv4 temp = *this;
        increment();
        return temp;
    }

    IPv4 &operator--()
    {
        decrement();
        return *this;
    }

    IPv4 operator--(int)
    {
        IPv4 temp = *this;
        decrement();
        return temp;
    }

    friend bool operator==(const IPv4 &lhs, const IPv4 &rhs)
    {
        return lhs.address == rhs.address;
    }

    friend bool operator!=(const IPv4 &lhs, const IPv4 &rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const IPv4 &lhs, const IPv4 &rhs)
    {
        return lhs.address < rhs.address;
    }

    friend bool operator>(const IPv4 &lhs, const IPv4 &rhs)
    {
        return rhs < lhs;
    }

    friend bool operator<=(const IPv4 &lhs, const IPv4 &rhs)
    {
        return !(rhs < lhs);
    }

    friend bool operator>=(const IPv4 &lhs, const IPv4 &rhs)
    {
        return !(lhs < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const IPv4 &ip)
    {
        os << static_cast<int>(ip.address[0]) << '.'
           << static_cast<int>(ip.address[1]) << '.'
           << static_cast<int>(ip.address[2]) << '.'
           << static_cast<int>(ip.address[3]);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, IPv4 &ip)
    {
        std::string ip_str;

        is >> ip_str;
        if (is.fail())
            return is;

        std::stringstream ss(ip_str);
        std::string segment;

        for (int i = 0; i < 4; ++i)
        {
            if (!std::getline(ss, segment, '.'))
            {
                is.setstate(std::ios::failbit);
                return is;
            }

            try
            {
                unsigned long val = std::stoul(segment);

                if (val > 255)
                {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                ip.address[i] = static_cast<std::uint8_t>(val);
            }
            catch (const std::exception &)
            {
                is.setstate(std::ios::failbit);
                return is;
            }
        }

        if (ss.peek() != std::stringstream::traits_type::eof())
        {
            is.setstate(std::ios::failbit);
        }

        return is;
    }

private:
    std::array<uint8_t, 4> address;

    void increment()
    {
        for (int i = 3; i >= 0; --i)
        {
            if (address[i] != 255)
            {
                ++address[i];
                return;
            }
            else
            {
                address[i] = 0;
            }
        }
    }

    void decrement()
    {
        for (int i = 3; i >= 0; --i)
        {
            if (address[i] != 0)
            {
                --address[i];
                return;
            }
            else
            {
                address[i] = 255;
            }
        }
    }
};

static_assert(sizeof(IPv4) == 4, "IPv4 should be exactly 4 bytes");

void test_constructors()
{
    IPv4 ip1;
    std::stringstream ss1;
    ss1 << ip1;
    assert(ss1.str() == "0.0.0.0");

    IPv4 ip2(192, 168, 1, 1);
    std::stringstream ss2;
    ss2 << ip2;
    assert(ss2.str() == "192.168.1.1");
}

void test_increment_decrement()
{
    IPv4 ip1(192, 168, 1, 1);
    ++ip1;
    std::stringstream ss1;
    ss1 << ip1;
    assert(ss1.str() == "192.168.1.2");

    IPv4 ip2(192, 168, 1, 1);
    IPv4 ip3 = ip2++;
    std::stringstream ss2, ss3;
    ss2 << ip2;
    ss3 << ip3;
    assert(ss2.str() == "192.168.1.2");
    assert(ss3.str() == "192.168.1.1");

    IPv4 ip4(192, 168, 1, 255);
    ++ip4;
    std::stringstream ss4;
    ss4 << ip4;
    assert(ss4.str() == "192.168.2.0");

    IPv4 ip5(255, 255, 255, 255);
    ++ip5;
    std::stringstream ss5;
    ss5 << ip5;
    assert(ss5.str() == "0.0.0.0");

    IPv4 ip6(192, 168, 1, 1);
    --ip6;
    std::stringstream ss6;
    ss6 << ip6;
    assert(ss6.str() == "192.168.1.0");

    IPv4 ip7(192, 168, 1, 1);
    IPv4 ip8 = ip7--;
    std::stringstream ss7, ss8;
    ss7 << ip7;
    ss8 << ip8;
    assert(ss7.str() == "192.168.1.0");
    assert(ss8.str() == "192.168.1.1");

    IPv4 ip9(192, 168, 1, 0);
    --ip9;
    std::stringstream ss9;
    ss9 << ip9;
    assert(ss9.str() == "192.168.0.255");

    IPv4 ip10(0, 0, 0, 0);
    --ip10;
    std::stringstream ss10;
    ss10 << ip10;
    assert(ss10.str() == "255.255.255.255");
}

void test_comparison_operators()
{
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);
    IPv4 ip3(192, 168, 1, 2);
    IPv4 ip4(10, 0, 0, 1);

    assert(ip1 == ip2);
    assert(!(ip1 == ip3));

    assert(ip1 != ip3);
    assert(!(ip1 != ip2));

    assert(ip1 < ip3);
    assert(ip4 < ip1);
    assert(!(ip1 < ip2));

    assert(ip3 > ip1);
    assert(ip1 > ip4);
    assert(!(ip1 > ip2));

    assert(ip1 <= ip2);
    assert(ip1 <= ip3);
    assert(!(ip3 <= ip1));

    assert(ip1 >= ip2);
    assert(ip3 >= ip1);
    assert(!(ip1 >= ip3));
}

void test_input_output()
{
    IPv4 ip1(192, 168, 1, 1);
    std::stringstream ss1;
    ss1 << ip1;
    assert(ss1.str() == "192.168.1.1");

    IPv4 ip2;
    std::stringstream ss2("10.20.30.40");
    ss2 >> ip2;
    assert(!ss2.fail());

    std::stringstream ss3;
    ss3 << ip2;
    assert(ss3.str() == "10.20.30.40");

    IPv4 ip3;
    std::stringstream ss4("10.20.30");
    ss4 >> ip3;
    assert(ss4.fail());

    IPv4 ip4;
    std::stringstream ss5("256.300.500.1000");
    ss5 >> ip4;
    assert(ss5.fail());

    IPv4 ip5;
    std::stringstream ss6("10.20.30.40.50");
    ss6 >> ip5;
    assert(ss6.fail());
}

int main()
{
    test_constructors();
    test_increment_decrement();
    test_comparison_operators();
    test_input_output();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}