#include <iostream>
#include <algorithm>
#include <numeric>
#include <assert.h>


int gcd (int a, int b)
{
    if (!b) return a;
    gcd(b, b % a);
}

int lcm(int a, int b){
    return a * b / (gcd(a, b));
}

int main(){
    assert(gcd(15, 2) == std::gcd(15, 2));
}