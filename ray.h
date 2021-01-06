#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {

    public:

       ray(){

       };

       ray(const vec3& origin, const vec3& direction) {
           o = origin;
           d = direction;
       };

       inline vec3 point_at_parameter(const float t) {
             return o + ( d * t);
        }

        vec3 o; //This is the origin of the ray
        vec3 d; //This is the direction of the ray

};


#endif