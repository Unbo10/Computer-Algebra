#include <iostream>
#include <vector>
#include "calculator.h"

int main() {
    std::cout << "Welcome!\n";
    Calculator calc;
    std::vector<int> num_b10 = calc.convert_to_b10(10011, 2);
    std::vector<int> res = calc.add(610, 4, 10);
    std::vector<int> res_base10 = calc.convert_to_b10(res, int(res.size()), 10);
    calc.print_vector(res_base10);
    std::cout << calc.mod(-4, 3) << "\n";
    res = calc.subtract(1100101, 101001, 2); //* 101 - 41 = 60 (111100)
    res = calc.multiply(101001, 1100101, 2); //* 101 * 41 = 4141 (1000000101101)
    std::cout << "Division\n";
    std::vector<int>* res_div = calc.divide(34501, 34, 10); //!ISSUE WHEN SIZES ARE THE SAME
    // delete res_div;
}