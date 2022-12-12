#pragma once

#include <math.h>
#include <vector>

#include <rational.h>

namespace cubic_spline {

class cubic_spline {
public:
    cubic_spline() = default;
    cubic_spline(double left, double right);
    cubic_spline(double left, double right, double (*f)(double));
    cubic_spline(double left, double right, int N);
    cubic_spline(double left, double right, int N, double (*f)(double));

    /* */
    rational::rational calculate_spline(rational::rational t);
private:
    int N_ = 10;
    double left_ = 0, right_ = 2 * M_PI, h = (right_ - left_) / N_;
    double (*f_)(double);

    std::vector<rational::rational> x,y;

    void build_spline();
    std::vector<std::vector<rational::rational> > make_spline_matrix();
    std::vector<rational::rational> make_spline_vector();
};

} // namespace cubic_spline