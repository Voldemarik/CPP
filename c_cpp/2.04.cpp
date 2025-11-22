#include <iostream>

int main(){
    int count = 0; 
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                if (!(i * i * i + j * j * j + k * k * k - i*100 - j*10 - k)){
                    std::cout << i * 100 + j * 10 + k << '\n';
                    ++count;
                }
            }
        }
    }
    std::cout << count;
}