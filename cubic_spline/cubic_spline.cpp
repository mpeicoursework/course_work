#include <cubic_spline.h>

#include <vector>
#include <iostream>

namespace cubic_spline {
    cubic_spline::cubic_spline(double left, double right): left_(left), right_(right) { h = (right_ - left) / N_; }

    cubic_spline::cubic_spline(double left, double right, double (*f)(double)) : left_(left), right_(right), f_(f) {
        h = (right_ - left) / N_; 
    }

    cubic_spline::cubic_spline(double left, double right, int N): N_(N) { cubic_spline(left, right); }

    cubic_spline::cubic_spline(double left, double right, int N, double (*f)(double)) : N_(N) {
        cubic_spline(left, right, f);
    }

    std::vector<std::vector<rational::rational> > cubic_spline::make_spline_matrix() {
        int n = N_;
        auto S = std::vector<std::vector<rational::rational> >(n, std::vector<rational::rational>(n, 1.0));
        for (int i = 1; i < n; ++i) {
            S[i - 1][i - 1] = 1 / h;
            S[i - 1][i] = 2 * (1 / h + 1 / h); 
            S[i - 1][i + 1] = 1 / h;
        }
        rational::rational r = 1 / h / h;
        S[n - 2][0] = r;
        S[n - 2][1] = 0.0;
        S[n - 2][2] = -r;
        S[n - 1][n - 3] = r;
        S[n - 1][n - 2] = 0.0;
        S[n - 1][n - 1] = -r;
        return S;
    }


    std::vector<rational::rational> cubic_spline::make_spline_vector() {
        int n = N_;
        auto v = std::vector<rational::rational>(n, rational::rational("1/1"));
        std::cout << "Here\n";
        for (int i = 0; i < n; ++i) {
            v[i - 1] = (1 / h / h * (y[i] - y[i - 1]) + 1 / h / h * (y[i + 1] - y[i])) * 3;
        }
        rational::rational r = 1.0 / (h * h * h);
        v[n - 2] = r * (y[1] - y[2]) * 2 - r * (y[0] - y[1]) * 2;
        v[n - 1] =  r * 2 * (y[n - 2] - y[n - 1]) - r * (y[n - 3] - y[n - 2]) * 2;
        return v;
    }

    rational::rational cubic_spline::calculate_spline(rational::rational t) {
        int n = N_;
        std::vector<std::vector<rational::rational> > A = make_spline_matrix();
        std::vector<rational::rational> b = make_spline_vector(); 
        auto [L, U] = tasks::LUDecomposition(A, rational::rational("0/1"), rational::rational("1/1"));
        std::vector<rational::rational> s = tasks::LUSolution(L, U, b);

        int i = 0;
        // TODO: maybe binary search ?
        for (int j = 1; j < n && !i; ++j) {
            if (t >= x[j - 1] && t <= x[j])
                i = j;
        }
        return y[i - 1] * ((t - x[i]) * (t - x[i]) * (t - x[i-1]) * 2 + h) / h / h / h + y[i] * 
                ((t - x[i - 1])* (t - x[i - 1]) * ((x[i] - t) * 2 + h)) / h / h / h + s[i - 1] * 
                ((t - x[i - 1]) * (t - x[i])*(t - x[i])) / h / h + s[i] * ((t - x[i - 1])* (t - x[i - 1])* (t - x[i])) / h / h;
    }
    
} // namespace cubic_spline