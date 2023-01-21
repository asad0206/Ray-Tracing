#ifndef VEC3_H
#define VEC3_H

#include <cmath>
// cmath looks small but is freaking godzilla of a header
// beware of it cuz it can bring maths
// and maths makes all confusing
#include <iostream>

using std::sqrt;

class vec3
{
public:
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // operator overloading for unary minus
    vec3 operator-() const
    {
        return vec3(-e[0], -e[1], -e[2]);
    }

    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    // operator overloading for unary plus
    // Returning by reference is better thus, *this
    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        // The this pointer is an implicit parameter to all member functions
        return *this;
    }

    // operator overloading for multiply
    vec3 &operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // operator overloading for divide
    vec3 &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    // near zero func, return true if it is very near to zero in all the dimensions
    bool near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions
        const auto s = 1e-8;
        // fabs() - to get the absolute value of a floating point number
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

public:
    double e[3];
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

// vec3 utility functions
// FINISH OPERATOR OVERLOADING cuz man RTW used it a lot and had to
// spend an our to read it and watch videos on YT to understand
inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vec3 &u, const vec3 &v)
{
    return ((u.e[0] * v.e[0]) + (u.e[1] * v.e[1]) + (u.e[2] * v.e[2]));
}

inline vec3 corss(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

// lambertian distribution
// it has a distribution of cos(ϕ).
// we can achive this by picking random points on the surface of the unit spehre
// so we pass the random_in_unit_sphere to the unit_vector
// now we have random units to get the offset values along the surface
vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

// uniform scatter direction | diffusion
// uniform scatter direction for all angles away from the hit point, with no dependence on the angle from the normal
// fast hack
/*vec3 random_in_hemisphere(const vec3 &normal)
{
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}*/

// vectors resultant to calc the reflected ray
vec3 reflect(const vec3 &v, const vec3 &n)
{
    // https://raytracing.github.io/books/RayTracingInOneWeekend.html#metal/mirroredlightreflection
    // refer diagram
    return v - 2 * dot(v, n) * n;
}

// snell's law - refaction function
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif