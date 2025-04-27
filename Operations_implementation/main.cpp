#include <iostream>
#include "../Numbers/Integer.cpp"

int main() {
    Integer number = 12318124, second = 9714987124;
    for(int i = 0; i < 10; i++)
        number += second;

    std::cout << number;
}