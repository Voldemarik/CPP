#include <iostream>
#include <climits>
#include <cmath>

#define sqrt_5  2.23606797749978969


int bine (int n){
    double temp  = std::round((std::pow((1.0 + sqrt_5), n) - std::pow((1.0 - sqrt_5), n)) / (std::pow(2.0, n)* sqrt_5));
    if (temp > INT_MAX + 1.0 - 1.0){
        return -1; 
    }
    else if (temp < INT_MIN + 1.0 - 1.0){
        return -1; 
    }
    return static_cast<int>(temp);
}

int main (){
    int n; 
    std::cin >> n;
    n = bine(n);
    if (!(n+1)) {
        std::cout << "num is too big";
        return 0; 
    }
    std::cout << n;
}