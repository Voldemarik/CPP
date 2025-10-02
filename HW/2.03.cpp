#include <iostream>

int main() {
    char c;
    while (std::cin >> c) {
        switch (c) {
            case '0' ... '9':
                std::cout << "Десятичные цифры" << std::endl;
                break;

            case 'A' ... 'Z':
                std::cout << "Заглавные буквы" << std::endl;
                break;
                
            case 'a' ... 'z':
                std::cout << "Строчные буквы" << std::endl;
                break;
                
            case '!': case '"': case '#': case '$': case '%': case '&': case '\'': 
            case '(': case ')': case '*': case '+': case ',': case '-': case '.': 
            case '/': case ':': case ';': case '<': case '=': case '>': case '?': 
            case '@': case '[': case '\\': case ']': case '^': case '_': case '`':
            case '{': case '|': case '}': case '~':
                std::cout << "Знаки препинания" << std::endl;
                break;
                
            default:
                std::cout << "Прочие символы" << std::endl;
                break;
        }
    }
}