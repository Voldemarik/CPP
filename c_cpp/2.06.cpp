#include <iostream>
#include <cmath>

int main(){
    size_t sz;
    std::cin >> sz;
    double nums[sz], min_val = __DBL_MAX__, max_val = -__DBL_MAX__, mid_val = 0.0, s_val=0.0;
    for (size_t i = 0; i < sz; ++i)
    {
        std::cin >> nums[i];
        mid_val += nums[i];
        min_val = std::min(nums[i], min_val);
        max_val = std::max(nums[i], max_val);
    }
    mid_val /= sz;
    std::cout << "Минимальное значение: " << min_val
              << "\nМаксимальное значение: " << max_val 
              << "\nСреднее значение: " << mid_val;
    for (auto num : nums )
    {
        s_val += (num - mid_val) * (num - mid_val);
    }
    std::cout << "\nСтандартное отклонение: " << std::sqrt(s_val / (sz));
}
