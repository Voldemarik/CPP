#include <iostream>



int main(){
    double current_elem = 1.0, sum = 0, eps;
    int iter = 1;
    std::cin >> eps;
    do
    {
        sum += current_elem;
        current_elem /= iter;
        ++iter;
    } while (current_elem > eps);
    std::cout << sum;
}