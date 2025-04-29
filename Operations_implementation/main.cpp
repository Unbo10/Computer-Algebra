#include <iostream>
#include "../Numbers/Integer.cpp"

int main() {
    Integer number = 91724091724171241, number2 = 8782141;

    std::cout << number/number2 << std::endl;
    std::cout << Integer(10)/Integer(3) << std::endl;
}