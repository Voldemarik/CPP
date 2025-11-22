#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

template <typename T>
void order(std::vector<T> &vector, std::size_t left, std::size_t right)
{
    for (auto i = left + 1; i < right; ++i)
    {
        for (auto j = i; j > left; --j)
        {
            if (vector[j - 1] > vector[j])
            {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::size_t partition(std::vector<T> &vector, std::size_t left, std::size_t right)
{
    auto pivot_index = std::midpoint(left, right);
    int pivot = vector[pivot_index];

    std::swap(vector[pivot_index], vector[right - 1]);

    std::size_t i = left;
    for (auto j = left; j < right - 1; ++j)
    {
        if (vector[j] <= pivot)
        {
            std::swap(vector[i], vector[j]);
            ++i;
        }
    }

    std::swap(vector[i], vector[right - 1]);
    return i;
}

////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void split(std::vector<T> &vector, std::size_t left, std::size_t right)
{
    if (right - left > 16)
    {
        auto pivot_index = partition(vector, left, right);

        split(vector, left, pivot_index);
        split(vector, pivot_index + 1, right);
    }
    else
    {
        order(vector, left, right);
    }
}

////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void sort(std::vector<T> &vector)
{
    split(vector, 0, std::size(vector));
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto size = 1'000uz;

    std::vector<double> vector(size, 0);

    for (auto i = 0uz; i < size; ++i)
    {
        vector[i] = std::rand();
    }

    sort(vector);
    assert(std::is_sorted(vector.begin(), vector.end()));
}