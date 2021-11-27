cmake_minimum_required(VERSION 3.10)

project(Pathtracer)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(pathtracer main.cpp sphere.h sphere.cpp hittable_list.h hittable_list.cpp  hittable.h vec3.cpp vec3.h ray.h rtweekend.h color.h)
