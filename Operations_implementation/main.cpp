#include <iostream>
#include "../Numbers/Integer.cpp"

Integer testingFunc()
{
    return 12413;
}

int main() {
    Integer number = 26, number2 = 16;
    std::cout << testingFunc() << std::endl;
}