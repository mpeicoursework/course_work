#include <utils.h>

namespace utils {

    long long gcd (int a, int b) {
	    return b ? gcd (b, a % b) : a;
    }

    long long lcm (int a, int b) {
	    return a / gcd (a, b) * b;
    }
    
}