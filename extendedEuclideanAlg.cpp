#include <iostream>
#include <vector>

void print_list(int* list, int size) {
    std::cout << "[";
    for(int i = 0; i < size - 1; i++) 
        std::cout << list[i] << ", ";
    std::cout << list[size - 1] << "]";
}

int* extendedEuclAlg(int* u, int* v) {
    int r[3];
    int q;
    while(r[0] != 0) {
        q = u[0] / v[0];
        r[0] = u[0] - q*v[0];
        r[1] = u[1] - q*v[1];
        r[2] = u[2] - q*v[2];
        for(int i = 0; i < 3; i++) {
            u[i] = v[i];
        }
        std::cout << "u: ";
        print_list(u, 3);
        for(int i = 0; i < 3; i++) {
            v[i] = r[i];
        }
        std::cout << "---v";
        print_list(v, 3);
        std::cout << "---r";
        print_list(r, 3);
        std::cout << "\n";
    }
    return u;
}

int* extendedEuclAlg(int a, int b) {
    int u[3] = {a, 1, 0};
    int v[3] = {b, 0, 1};
    return extendedEuclAlg(u, v);
}

int main() {
    int* result = extendedEuclAlg(3811500, 463736);
    for(int i = 0; i < 3; i++) {
        std::cout << result[i] << " | ";
    }
    std::cout << "\n";
}