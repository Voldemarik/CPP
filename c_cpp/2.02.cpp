#include <iostream>
#include <cmath>
#include <limits>

int main() 
{
    double a, b, c;
    std::cin >> a >> b >> c;
    
    double d = b * b - 4 * a * c;
        
    if (std::abs(d) == 0.0) {
        double x = -b / (2 * a);
        std::cout << "x = " << x << std::endl;
    } else if (d > 0) {
        double sqrt_d = std::sqrt(d);
        double x1 = (-b - sqrt_d) / (2 * a);
        double x2 = (-b + sqrt_d) / (2 * a);
        std::cout << "x1 = " << x1 << ", x2 = " << x2 << std::endl;
    } else {
        double r_p = -b / (2 * a);
        double i_p = std::sqrt(-d) / (2 * a);
        std::cout << "x1 = " << r_p << " + " << i_p << "i, "
                << "x2 = " << r_p << " - " << i_p << "i" << std::endl;
    }
}