#include <cmath>
#include <numbers>
#include <cassert>
#include <vector>
#include <memory>

class Shape
{
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() = default;
};

class Triangle : public Shape
{
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double area() const override final
    {
        double p = (a + b + c) / 2;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

    double perimeter() const override final { return a + b + c; }

private:
    double a, b, c;
};

class Square final : public Shape
{
public:
    Square(double side) : side(side) {}

    double area() const override { return side * side; }

    double perimeter() const override { return 4 * side; }

private:
    double side;
};

class Circle final : public Shape
{
public:
    Circle(double radius) : radius(radius) {}

    double area() const override { return radius * radius * std::numbers::pi; }

    double perimeter() const override { return 2 * radius * std::numbers::pi; }

private:
    double radius;
};

int main()
{
    Triangle abc(3, 4, 5);
    assert(std::fabs(abc.area() - 6.0) < 0.0001 && std::fabs(abc.perimeter() - 12.0) < 0.0001);

    Square sq(4.0);
    assert(std::fabs(sq.area() - 16.0) < 0.0001 && std::fabs(sq.perimeter() - 16.0) < 0.0001);

    Circle circle(4.0);
    assert(std::fabs(circle.perimeter() - 25.1327) < 0.0001 && std::fabs(circle.area() - 50.2655) < 0.0001);

    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));
    shapes.push_back(std::make_unique<Square>(4.0));
    shapes.push_back(std::make_unique<Circle>(4.0));

    for (const auto &shape : shapes)
    {
        [[maybe_unused]] double area = shape->area();
        [[maybe_unused]] double perimeter = shape->perimeter();
    }

    return 0;
}