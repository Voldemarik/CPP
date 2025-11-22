#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <cassert>
#include <stdexcept>

template <typename T>
class Vector
{
public:
    Vector() : m_array(nullptr), m_size(0), m_capacity(0) {}

    Vector(std::initializer_list<T> list) : m_size(std::size(list)),
                                            m_capacity(std::size(list))
    {
        m_array = m_size ? new T[m_capacity]{} : nullptr;
        std::ranges::copy(list, m_array);
    }

    Vector(Vector const &other) : m_size(other.m_size),
                                  m_capacity(other.m_capacity)
    {
        m_array = m_capacity ? new T[m_capacity]{} : nullptr;
        std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
    }

    Vector(Vector &&other) noexcept
        : m_array(std::exchange(other.m_array, nullptr)),
          m_size(std::exchange(other.m_size, 0)),
          m_capacity(std::exchange(other.m_capacity, 0))
    {
    }

    ~Vector()
    {
        delete[] m_array;
    }

    auto &operator=(Vector other)
    {
        swap(other);
        return *this;
    }

    void swap(Vector &other) noexcept
    {
        std::swap(m_array, other.m_array);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    std::size_t capacity() const { return m_capacity; }
    std::size_t size() const { return m_size; }

    bool empty() const { return m_size == 0; }
    void clear() { m_size = 0; }

    void push_back(T value)
    {
        if (m_size >= m_capacity)
        {
            grow();
        }

        m_array[m_size] = value;
        ++m_size;
    }

    T &operator[](std::size_t index)
    {
        assert(index < m_size);
        return m_array[index];
    }

    const T &operator[](std::size_t index) const
    {
        assert(index < m_size);
        return m_array[index];
    }

private:
    T *m_array = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;

    void grow()
    {
        std::size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;

        T *new_array = new T[new_capacity]{};

        if (m_size > 0)
        {
            std::ranges::copy(m_array, m_array + m_size, new_array);
        }

        delete[] m_array;

        m_array = new_array;
        m_capacity = new_capacity;
    }
};

template <typename T>
void swap(Vector<T> &lhs, Vector<T> &rhs) noexcept
{
    lhs.swap(rhs);
}

int main()
{
    Vector<int> v1;
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
    assert(v1.empty());

    Vector<int> v2 = {10, 20, 30, 40, 50, 60};
    assert(v2.size() == 6);
    assert(v2.capacity() == 6);
    assert(!v2.empty());
    assert(v2[0] == 10 && v2[5] == 60);

    Vector<int> v3 = v2;
    assert(v3.size() == 6);
    assert(v3.capacity() == 6);
    assert(v3[0] == 10 && v3[5] == 60);

    Vector<int> v4 = std::move(v3);
    assert(v4.size() == 6);
    assert(v4.capacity() == 6);
    assert(v4[0] == 10 && v4[5] == 60);
    assert(v3.size() == 0);
    assert(v3.capacity() == 0);
    assert(v3.empty());

    v3 = v2;
    assert(v3.size() == 6);
    assert(v3.capacity() == 6);
    assert(v3[0] == 10 && v3[5] == 60);

    v4 = std::move(v3);
    assert(v4.size() == 6);
    assert(v4.capacity() == 6);
    assert(v4[0] == 10 && v4[5] == 60);
    assert(v3.size() == 0);
    assert(v3.capacity() == 0);

    Vector<int> v5 = {100, 200};
    Vector<int> v6 = {300, 400, 500, 600};
    swap(v5, v6);

    assert(v5.size() == 4);
    assert(v5.capacity() == 4);
    assert(v5[0] == 300 && v5[3] == 600);

    assert(v6.size() == 2);
    assert(v6.capacity() == 2);
    assert(v6[0] == 100 && v6[1] == 200);

    Vector<int> v7;
    assert(v7.capacity() == 0);

    v7.push_back(11);
    assert(v7.size() == 1);
    assert(v7.capacity() == 1);
    assert(v7[0] == 11);

    v7.push_back(22);
    assert(v7.size() == 2);
    assert(v7.capacity() == 2);
    assert(v7[1] == 22);

    v7.push_back(33);
    assert(v7.size() == 3);
    assert(v7.capacity() == 4);
    assert(v7[2] == 33);

    v7.push_back(44);
    assert(v7.size() == 4);
    assert(v7.capacity() == 4);

    v7.push_back(55);
    assert(v7.size() == 5);
    assert(v7.capacity() == 8);
    assert(v7[4] == 55);

    v7.clear();
    assert(v7.size() == 0);
    assert(v7.capacity() == 8);
    assert(v7.empty());

    v7.push_back(99);
    assert(v7.size() == 1);
    assert(v7.capacity() == 8);
    assert(v7[0] == 99);

    return 0;
}