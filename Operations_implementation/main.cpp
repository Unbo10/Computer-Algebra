#include <iostream>
#include <vector>
#include "calculator.h"
#include "../utils/List.cpp"

int main() {
    List<int> list;
    
    for(int i = 0; i < 10; i++)
    {
        list.add(i);
        std::cout << list;
    }
    list.pop(5);
    std::cout << list;
}