set(TARGET pathtracer)

add_executable(${TARGET} main.cpp sphere.cpp  moving_sphere.cpp hittable_list.cpp vec3.cpp)