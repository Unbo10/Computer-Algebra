#include <iostream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.cpp"

int main() {
    Integer dividen = 101, divisor = 127412;
    Integer::changeBase(2, dividen);
    Integer::changeBase(2, divisor);
    std::cout << dividen.getBase() << "   " << divisor.getBase() << std::endl;
    std::cout << divisor/dividen;
}