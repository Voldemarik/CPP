#include <iostream>

int main() {
    char c;
    while (std::cin >> c) {
        switch (c) {
            case '0' ... '9':
                std::cout << "Decimal" << std::endl;
                break;

            case 'A' ... 'Z':
                std::cout << "Main" << std::endl;
                break;
                
            case 'a' ... 'z':
                std::cout << "String" << std::endl;
                break;
                
            case '!': case '"': case '#': case '$': case '%': case '&': case '\'': 
            case '(': case ')': case '*': case '+': case ',': case '-': case '.': 
            case '/': case ':': case ';': case '<': case '=': case '>': case '?': 
            case '@': case '[': case '\\': case ']': case '^': case '_': case '`':
            case '{': case '|': case '}': case '~':
                std::cout << "Pointer" << std::endl;
                break;
                
            default:
                std::cout << "Another" << std::endl;
                break;
        }
    }
}