#include <tasks.h>

#include <iostream>
#include "stdio.h"
#include "string.h"
#include "math.h"

namespace tasks {
    rational::rational pow(rational::rational basis, int exponent) {
        if (exponent == 0)
		    return rational::rational(1,1);
	    if (exponent % 2)
		    return pow(basis, exponent - 1) * basis;
	    else {
		    rational::rational buffer = pow(basis, exponent >> 1);
		    return buffer * buffer;
	    }
    }

    /* 
    Извлечение корня 'root' степени  методом Ньютона: 
    f(x) = x^n - basis, тогда решение f(x) = 0 и будет искомым корнем
    */
    rational::rational root(rational::rational basis, int root) {
        rational::rational precision(1, 1'000'000'000'000);
        rational::rational x1, x0 = basis / 2;
        x1 = (basis / pow(x0, root-1) - x0) / root;
        while (abs(x1 - x0) < precision) {
            x0 = x1;
            x1 = (basis / pow(x0, root-1) - x0) / root;
        }
        return x1;
    }
}