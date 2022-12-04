#include <rational.h>

#include <iostream>

int main() {
    rational::rational r13("-1.52");
    rational::rational r14("0.49");
    rational::rational r15 = r13 + r14;
    std::cout << r15;
}