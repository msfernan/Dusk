#pragma once

#include "vec3.h"

class ray {

    public:

       ray(){

       };

       ray(const vec3& origin, const vec3& direction, double time = 0.0) {
           o = origin;
           d = direction;
           tm = time;
       };

       inline vec3 point_at_parameter(const float t) const{
             return o + ( d * t);
       }

       inline vec3 origin() const{
            return o;
       }

       inline vec3 direction() const {
            return d;
       }

       inline double time() const {
             return tm;
       }

       inline vec3 at(double t) const {
            return o + t * d;
       }

    private:
        vec3 o; //This is the origin of the ray
        vec3 d; //This is the direction of the ray
        double tm; //Time for which the ray lasts

};
