#include "vec3.h"


#if 0
std::istream& operator>>(std::istream &is, vec3 &v){
   is >> v.x() >> v.y() >> v.z();
   return is;
}
#endif

std::ostream& operator<<(std::ostream &os, const vec3 &v){
   os << v.x() << " " << v.y() << " " << v.z();
   return os;
}



vec3& vec3::operator+=(const vec3 &v){
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}


vec3& vec3::operator-=(const vec3 &v){
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return *this;

}


vec3& vec3::operator*=(const vec3 &v){
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();
    return *this;

}

vec3& vec3::operator/=(const vec3 &v){
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();
    return *this;

}


vec3& vec3::operator*=(const float t){
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;

}

vec3& vec3::operator/=(const float t){
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;

}


vec3 operator*(const vec3 &v1, const vec3 &v2){
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}


vec3 operator*(const vec3 &v1, float t){
    return vec3(v1.x() * t, v1.y() * t, v1.z() * t);
}

vec3 operator*(float t, const vec3 &v1){
    return vec3(v1.x() * t, v1.y() * t, v1.z() * t);
}


vec3 operator+(const vec3 &v1, const vec3 &v2){
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

vec3 operator-(const vec3 &v1, const vec3 &v2){
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

vec3 operator/(const vec3 &v1, const vec3 &v2){
    return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

vec3 operator/(const vec3 &v1, float t){
    return vec3(v1.x() / t, v1.y() / t, v1.z() / t);
}

vec3 operator/(float t, const vec3 &v1){
    return vec3(v1.x() / t, v1.y() / t, v1.z() / t);
}


float dot(const vec3 &v1, const vec3 &v2) {
    return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
}


vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3(   v1.y() * v2.z() - v1.z() * v2.y(),  
                 -(v1.x() * v2.z() - v1.z() * v2.x()),
                   v1.x() * v2.y() - v1.y() * v2.x()
                );
}


vec3 unit_vector(const vec3 &v1) {
    float length = v1.length();
    return (v1 / length);
}


vec3 random_in_unit_sphere()  {

    while(true) {

        auto p = vec3::random(-1, 1);
        if(p.length_squared() <= 1) continue;
        return p;

    }
}


vec3 random_in_hemisphere(const vec3& normal) {

    vec3 in_unit_sphere = random_in_unit_sphere();

    if(dot(in_unit_sphere, normal) > 0.0) { //In the same hemisphere as normal

        return in_unit_sphere;
    }
    else {
        return -in_unit_sphere;
    }
}


vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(vec3::random_double(-1,1), vec3::random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}