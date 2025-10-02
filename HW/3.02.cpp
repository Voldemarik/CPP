#include <cmath>
#include <numbers>

class Triangle
{
    double a, b, c; 

public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
    
    double perimeter() const {
        return a + b + c;
    }
    
    double square() const {
        double p = perimeter() / 2;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class Square
{
    double side;

    public:
    Square(double side) : side(side) {}
    
    double perimeter() const {
        return 4 * side;
    }
    
    double square() const {
        return side * side;
    }
};

class Circle
{
    double radius;
    
    public:
    Circle(double radius) : radius(radius) {}
    
    double perimeter() const {
        return 2 * radius * std::numbers::pi;
    }
    
    double square() const {
        return radius * radius * std::numbers::pi;
    }
};