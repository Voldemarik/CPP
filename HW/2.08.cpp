#include <iostream>
#include <vector>

using ULL = unsigned long long;
using USI = unsigned short int;

ULL collatz(ULL num, std::vector<ULL> &vec) {
    if (num == 1) {
        return 1;
    }
    
    if (num <= vec.size() && vec[num-1] != 0) {
        return vec[num-1];
    }
    
    ULL result;
    if (num % 2) {  
        result = collatz(3 * num + 1, vec) + 1;
    } else {             
        result = collatz(num / 2, vec) + 1;
    }
    
    if (num > vec.size()) {
        vec.resize(num);
    }
    vec[num-1] = result;
    
    return result;
}

int main() {
    USI min_num = 0, max_num = 100;

    std::vector<ULL> vec(max_num, 0);
    ULL max_length = 0, max_start = 0;
    
    for (ULL num = min_num; num <= max_num; ++num) {
        ULL length = collatz(num, vec);
        
        if (length > max_length) {
            max_length = length;
            max_start = num;
        }
    }
    
    std::cout << "Наибольшая длина: " << max_length 
              << "\nНачальное значение: " << max_start << std::endl;
}