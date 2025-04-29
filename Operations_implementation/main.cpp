#include <iostream>
#include "../Numbers/Integer.cpp"

int main() {
    Integer number = 91724091724171241, number2 = 8782141;

    std::cout << number/number2 << std::endl;
    std::cout << Integer(10) << std::endl;
    std::cout << Integer(123456789)/Integer(12345) << std::endl;
}