#pragma once

#include <rational.h>

namespace tasks {
    /* Бинарное возведение в степень 'exponent' за O(log(exponent)) */
    rational::rational pow(rational::rational basis, int exponent);

    /* Извлечение корня 'root' степени из basis */
    rational::rational root(rational::rational basis, int root);
}
