#include <rational.h>
#include <tasks.h>

#include <iostream>

int main() {
     rational::rational r1("11/2");
    rational::rational r2("11/2");
    rational::rational r = r1 + r2;
    std::cout << r << std::endl;
    std::cout << "1/4 = " << static_cast<double>(1) / static_cast<double>(4) << std::endl; 

    std::vector<std::vector<double>> matrix(3);
    matrix[0].push_back(9);
    matrix[0].push_back(0);
    matrix[0].push_back(-11);
    matrix[1].push_back(-9);
    matrix[1].push_back(8);
    matrix[1].push_back(6);
    matrix[2].push_back(18);
    matrix[2].push_back(-80);
    matrix[2].push_back(32);
    auto [L, U] = tasks::LUDecomposition(matrix, static_cast<double>(0), static_cast<double>(1));
    std::cout << "LU finish" << std::endl;
    std::cout << "L[0][0] = " << L[0][0] << std::endl;
    std::cout << "L[0][1] = " << L[0][1] << std::endl;
    std::cout << "L[0][2] = " << L[0][2] << std::endl;
    std::cout << "L[1][0] = " << L[1][0] << std::endl;
    std::cout << "L[1][1] = " << L[1][1] << std::endl;
    std::cout << "L[1][2] = " << L[1][2] << std::endl;
    std::cout << "L[2][0] = " << L[2][0] << std::endl;
    std::cout << "L[2][1] = " << L[2][1] << std::endl;
    std::cout << "L[2][2] = " << L[2][2] << std::endl;

    std::cout << "LU finish" << std::endl;
    std::cout << "U[0][0] = " << U[0][0] << std::endl;
    std::cout << "U[0][1] = " << U[0][1] << std::endl;
    std::cout << "U[0][2] = " << U[0][2] << std::endl;
    std::cout << "U[1][0] = " << U[1][0] << std::endl;
    std::cout << "U[1][1] = " << U[1][1] << std::endl;
    std::cout << "U[1][2] = " << U[1][2] << std::endl;
    std::cout << "U[2][0] = " << U[2][0] << std::endl;
    std::cout << "U[2][1] = " << U[2][1] << std::endl;
    std::cout << "U[2][2] = " << U[2][2] << std::endl;
    std::vector<double> b = {-13, 11, 2};

    std::vector<double> x = tasks::LUSolution(L, U, b);
    std::cout << "x[0] = " << x[0] << std::endl;
    std::cout << "x[1] = " << x[1] << std::endl;
    std::cout << "x[2] = " << x[2] << std::endl;

    return 0;
}