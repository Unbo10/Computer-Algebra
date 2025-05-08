#include <iostream>
#include "../Numbers/Integer.cpp"
#include "../Numbers/Number.cpp"
#include "../Numbers/Rational.cpp"

int main() {
    Integer m = 7000, m2 = 4500, k = -1;
    List<Integer> gcd = Integer::extendEuclidean(m, m2);

    std::cout << gcd[0] << " =? " << m*gcd[1] + m2*gcd[2];
}