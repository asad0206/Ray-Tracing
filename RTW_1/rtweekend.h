// literally defining pi for use in the code >_<
#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
// Returns the special value "positive infinity", as represented by the
// floating-point type T. Only meaningful if
// std::numeric_limits<T>::has_infinity == true
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double()
{
    // returns a random real number in range (0,1)
    return rand() / (RAND_MAX + 1.0);
    // RAND_MAX > 32767 always
    // and dividing by a huge number is better cuz we get more varied
    // decimals even at small incremets of the denominator
}

// if we want to use full c++ to get random numbers this is cpp code
/*inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}*/

inline double random_double(double min, double max)
{
    // returns a random real number in (min, max)
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// Common Headers

#include "ray.h"
#include "vec3.h"

#endif