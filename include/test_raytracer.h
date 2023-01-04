#pragma once

#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "test_raytracer.h"

void check_version_cpp();

vec3 color_pixel(const ray& r);

void write_test_ppm();

void write_test_ppm_vec3();

void write_test_ppm_ray();

void write_test_ppm_commandline();

void test_vec3();

void test_ray();