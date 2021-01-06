cmake_minimum_required(VERSION 3.10)

project(Pathtracer)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(pathtracer main.cpp vec3.cpp vec3.h ray.h)