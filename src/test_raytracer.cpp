#include "test_raytracer.h"

void check_version_cpp() {

    if(__cplusplus > 201703L) std::cout << "C++20\n";
    else if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";

}

vec3 color_pixel(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float y_value = unit_direction.y(); //This value will affect the lerp between -1 and 1
    float scaled_y_value = (y_value + 1)/2; //Scale so value between 0 and 1
    vec3 white(1.0, 1.0, 1.0);
    vec3 blue(0.5, 0.7, 1.0);
    vec3 lerp_color = (1.0 - scaled_y_value) * white + (scaled_y_value) * blue;
    return lerp_color;
}

void write_test_ppm() {

    int nx = 200;
    int ny = 100;


    std::ofstream ofs;


    try {

        ofs.open("test.ppm", std::ios::binary);

        ofs << "P3 \n" << nx << " " << ny << "\n255\n";

        for(int j = ny - 1; j >= 0; j--) {
            for(int i = 0; i < nx; i++) {
                float r = float(i) / float(nx);
                float g = float(j) / float(ny);
                float b  = 0.2; 
                int ir = int(255.99 * r);
                int ig = int(255.99 * g);
                int ib = int(255.99 * b);

                ofs << ir << " " << ig << " " << ib << "\n";

            }

        }

        ofs.close(); 
    }

    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    } 

}

void write_test_ppm_vec3() {

    int nx = 200;
    int ny = 100;


    std::ofstream ofs;


    try {

        ofs.open("test_vec3.ppm", std::ios::binary);

        ofs << "P3 \n" << nx << " " << ny << "\n255\n";

        for(int j = ny - 1; j >= 0; j--) {
            for(int i = 0; i < nx; i++) {

                vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
                int ir = int(255.99 * col[0]);
                int ig = int(255.99 * col[1]);
                int ib = int(255.99 * col[2]);

                ofs << ir << " " << ig << " " << ib << "\n";

            }

        }

        ofs.close(); 
    }

    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    } 

}

void write_test_ppm_ray() {

    int nx = 200;
    int ny = 100;


    std::ofstream ofs;


    try {

        ofs.open("test_ray.ppm", std::ios::binary);

        ofs << "P3 \n" << nx << " " << ny << "\n255\n";

        vec3 lower_left_corner(-2.0, -1.0, -1.0);
        vec3 horizontal(4.0, 0.0, 0.0);
        vec3 vertical(0.0, 2.0, 0.0);
        vec3 origin(0.0, 0.0, 0.0);

        for(int j = ny - 1; j >= 0; j--) {
            for(int i = 0; i < nx; i++) {

                float u = float(i) / float(nx);
                float v = float(j) / float(ny);

                ray r(origin, lower_left_corner + (u * horizontal) + (v * vertical));

                vec3 col = color_pixel(r);
                int ir = int(255.99 * col[0]);
                int ig = int(255.99 * col[1]);
                int ib = int(255.99 * col[2]);

                ofs << ir << " " << ig << " " << ib << "\n";

            }

        }

        ofs.close(); 
    }

    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    } 

}

//In order to use do ./a.out > testimage.ppm.
//WARN: Command line cant print out anything else to std::cout 
void write_test_ppm_commandline() {

    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j  = ny - 1; j >= 0; j--){

        for(int i = 0; i < nx; i++){
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            std::cout << ir << " " << ig << " " << ib << "\n";

        }
    }
}


void test_vec3() {

    vec3 col(10.0, 10.0, 10.0);
    std::cout << "Testing " <<  col.r() << std::endl;

    std::cout << "Testing dot product " << dot(col, col) << std::endl;

    vec3 mul = col * col;
    vec3 add = col + col;
    vec3 sub = col - col;
    vec3 div = col / col;

    std::cout << "Testing multiplication " << mul.x() << std::endl;

    std::cout << "Testing addition " << add.x() << std::endl;

    std::cout << "Testing subtraction " << sub.x() << std::endl;

    std::cout << "Testing division " << div.x() << std::endl;

    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(10.0, 2.0, 4.0);

    vec3 vcross = cross(v1, v2);

    std::cout << "Testing cross product " <<  vcross.x() << " " << vcross.y() << " " << vcross.z() << " " << std::endl;

    v1 += v2;
    std::cout << "Testing += " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;

    v1 -= v2;
    std::cout << "Testing -= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;


    v1 *= v2;
    std::cout << "Testing *= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;


    v1 /= v2;
    std::cout << "Testing /= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;

    v1 *= 10;
    std::cout << "Testing *= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;

    v1 /= 10;
    std::cout << "Testing *= " <<  v1.x() << " " << v1.y() << " " << v1.z() << " " << std::endl;


    float len = v1.length();
    std::cout << " Length " <<  len << std::endl;


    float sq_len = v1.length_squared();
    std::cout << "Squared length " <<  sq_len << std::endl;

    std::cout <<  "Testing vector output " << v1 << std::endl;

    std::cout <<  "v1[0] " << v1[0] << " v1[1] " << v1[1] << " v1[2] " << v1[2] << std::endl;

    v1[0] = 9.0;
    v1[1] = 8.0;
    v1[2] = 8.09;
    std::cout <<  "v1[0] " << v1[0] << " v1[1] " << v1[1] << " v1[2] " << v1[2] << std::endl;

    v1[0] = 2.0;
    v1[1] = 0.0;
    v1[2] = 1.0;

    std::cout << "v1 is " << v1 << std::endl;

    len = v1.length();
    std::cout << "The length is " << len << std::endl;

    vec3 unit_vec = unit_vector(v1);
    std::cout << "Unit vector " << unit_vec << std::endl;

    len = unit_vec.length();
    std::cout << "The unit length is " << len << std::endl;

}


void test_ray() {

    vec3 origin(1.0, 2.0, 3.0);
    vec3 direction(1.1, 2.1, 3.1);

    ray test_ray(origin, direction);
    //std::cout << "Testing ray origin ... "<< test_ray.o << std::endl;
    //std::cout << "Testing ray direction ... "<< test_ray.d << std::endl;

    vec3 point_test1;
    point_test1 = test_ray.point_at_parameter(1);
    std::cout << "point test " << point_test1 << std::endl;

    point_test1 = test_ray.point_at_parameter(10);
    std::cout << "point test " << point_test1 << std::endl;

}