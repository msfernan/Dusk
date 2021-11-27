#pragma once

#include "hittable.h"

#include <memory>
#include <vector>


using std::shared_ptr;
using std::make_shared; //This is so that we dont use std::make_shared. We can use make_shared.

class hittable_list : public hittable {
    public :
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object);}

        bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

    public :
        std::vector<shared_ptr<hittable>> objects;

};


