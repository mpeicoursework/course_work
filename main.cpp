#include <rational.h>

#include <iostream>

int main() {
    rational::rational r1(25,10);
    rational::rational r2(3,4);
    std::cout << r1 + r2 << "\n" << r1 * r2 << "\n" << r1 / r2 << "\n";
}