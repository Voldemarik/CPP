#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

struct Rectangle
{
    double X0, Y0, X1, Y1;
};

double IntersectionSquare(vector<Rectangle> &rect)
{
    if (rect.empty())
    {
        return 0.0;
    }

    double x0 = rect[0].X0, y0 = rect[0].Y0, x1 = rect[0].X1, y1 = rect[0].Y1;

    for (auto it : rect)
    {
        if (it.X0 >= x1 || it.X1 <= x0 || it.Y0 >= y1 || it.Y1 <= y0)
        {
            return 0;
        }
        x0 = max(x0, it.X0);
        x1 = min(x1, it.X1);
        y0 = max(y0, it.Y0);
        y1 = min(y1, it.Y1);
    }
    return (x1 - x0) * (y1 - y0);
}