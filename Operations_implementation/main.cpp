#include <iostream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.cpp"

int main() {
    Integer dividend, divisor;
    dividend = 1000;
    divisor = 950;

    Integer result;
    std::cout << dividend << "\n";
    result = dividend * divisor;
    std::cout << "Result: " << result;
    Integer dividen = 101, divisor = 127412;
    Integer::changeBase(2, dividen);
    Integer::changeBase(2, divisor);
    std::cout << dividen.getBase() << "   " << divisor.getBase() << std::endl;
    std::cout << divisor/dividen;
}