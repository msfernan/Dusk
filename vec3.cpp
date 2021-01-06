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


vec3 unit_vector(const vec3 &v1){
    float length = v1.length();
    return (v1 / length);
}


