#include <cassert>
#include <vector>
#include <iostream>

template <typename Container>
void handle(Container &container, int value)
{
    container.push_back(value);
}

template <typename Container, typename T>
void handle(Container &, T)
{
    static_assert(!std::is_same<T, int>::value, "Error not int");
}

////////////////////////////////////////////////////////////////

template <typename Container, typename... Args>
void insert_ints(Container &container, Args... args)
{
    (handle(container, args), ...);
}

////////////////////////////////////////////////////////////////

int main()
{
    std::vector<int> numbers;

    std::cout << "Initial size: " << numbers.size() << std::endl;

    insert_ints(numbers, 10, 3.14, 20, 1.0f);

    std::cout << "Final size: " << numbers.size() << std::endl;

    assert(numbers.size() == 2);

    assert(numbers[0] == 10);
    assert(numbers[1] == 20);

    std::vector<int> empty_vec;
    insert_ints(empty_vec, 1.1, "skip", 2.2f);

    assert(empty_vec.empty());
}