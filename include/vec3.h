#pragma once


#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3{

public:
    vec3() {
         e[0] = 0.0;
         e[1] = 0.0;
         e[2] = 0.0;

    }
    
    vec3(float e0, float e1, float e2) 
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }
    

    inline float x() const {return e[0];}
    inline float y() const {return e[1];}
    inline float z() const {return e[2];}
    inline float r() const {return e[0];}
    inline float g() const {return e[1];}
    inline float b() const {return e[2];}

    inline const vec3& operator+() const {return *this; }
    inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    inline float operator[](int i) const {return e[i];}
    inline float& operator[](int i) {return e[i];}

    vec3& operator+=(const vec3 &v);
    vec3& operator-=(const vec3 &v);
    vec3& operator*=(const vec3 &v);
    vec3& operator/=(const vec3 &v);
    vec3& operator*=(const float t);
    vec3& operator/=(const float t);


    inline float length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    inline float length_squared() const {
        return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }


    //local versions for use in vector class

    inline static double random_double() {
        // Returns a random real in [0,1).
        return rand() / (RAND_MAX + 1.0);
     }

    inline static double random_double(double min, double max) {
        // Returns a random real in [min,max).
        return min + (max - min) * random_double();
     }

    inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }


private:

    float e[3];

};

//Type aliases for vec3
using color = vec3;
using point3 = vec3;

std::ostream& operator<<(std::ostream &os, const vec3 &v);


float dot(const vec3 &v1, const vec3 &v2);

vec3 cross(const vec3 &v1, const vec3 &v2);

vec3 unit_vector(const vec3 &v1);

vec3 operator*(const vec3 &v1, const vec3 &v2);

vec3 operator*(const vec3 &v1, float t);

vec3 operator*(float t, const vec3 &v1);

vec3 operator+(const vec3 &v1, const vec3 &v2);

vec3 operator-(const vec3 &v1, const vec3 &v2);

vec3 operator/(const vec3 &v1, const vec3 &v2);

vec3 operator/(const vec3 &v1, float t);

vec3 operator/(float t, const vec3 &v1);

vec3 random_in_unit_sphere(); 

vec3 random_in_hemisphere(const vec3& normal);

vec3 random_unit_vector();

vec3 reflect(const vec3& v, const vec3& n);
