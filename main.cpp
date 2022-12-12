#include <rational.h>
#include <tasks.h>

#include <iostream>

int main() {
    rational::rational r1("11/2");
    rational::rational r2("11/2");
    rational::rational r = r1 + r2;
    std::cout << r << std::endl;
    std::cout << "1/4 = " << static_cast<double>(1) / static_cast<double>(4) << std::endl; 
    return 0;
}