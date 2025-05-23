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
}