#pragma once

#include <rational.h>

namespace tasks {
    /* Бинарное возведение в степень 'exponent' за O(log(exponent)) */
    rational::rational pow(rational::rational basis, int exponent);

    /* Извлечение корня 'root' степени из basis */
    rational::rational root(rational::rational basis, int root);


    template<typename T>
    std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>> 
    LUDecomposition(const std::vector<std::vector<T>>& matrix, T zero, T one) {
        size_t count_rows = matrix[0].size();
        std::vector<std::vector<T>> U = matrix;
        std::vector<std::vector<T>> L(count_rows, std::vector<T>(count_rows));
        for (size_t i = 0; i < count_rows; ++i) {
            for (size_t j = 0; j < count_rows; ++j) {
                if (i == j) {
                    L[i][j] = one;
                } else {
                    L[i][j] = zero;
                }
            }
        }

        for (size_t k = 0; k < count_rows - 1; ++k) {
            for (size_t i = k + 1; i < count_rows; ++i) {
                T mu_i_k = U[i][k] / U[k][k];
                L[i][k] = mu_i_k;
                U[i][k] -= U[k][k] * mu_i_k;
                for (size_t j = k + 1; j < count_rows; ++j) {
                    U[i][j] -= (mu_i_k * U[k][j]);
                }
            }
        }
        return std::make_tuple(L, U);
    }

    // LU solution the system of linear algebraic equations
    template<typename T> 
    std::vector<T> LUSolution(const std::vector<std::vector<T>>& L, const std::vector<std::vector<T>>& U, const std::vector<T>& b) {
        size_t count_rows = L[0].size();
        std::vector<T> y(count_rows);
        y[0] = b[0];
        for (size_t i = 1; i < count_rows; ++i) {
            y[i] = b[i];
            for (size_t j = 0; j < i; ++j) {
                y[i] -= L[i][j] * y[j];
            }
        }

        std::vector<T> x(count_rows);
        x[count_rows - 1] = y[count_rows - 1] / U[count_rows - 1][count_rows - 1];
        for (int64_t i = count_rows - 2; i > -1; --i) {
            T cur = y[i];
            for (int64_t j = count_rows - 1; j > i; --j) {
                cur -= U[i][j] * x[j];
            }
            x[i] = cur / U[i][i];
        }
        return x;
    }
}
